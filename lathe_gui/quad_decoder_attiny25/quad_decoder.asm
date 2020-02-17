; Quadrature decoder - totally optimized version. Tested in simulator and using signal generator: works as expected.
; Using raw ASM - compiles with avra - instead of avr-gcc
; The program does not use ISRs
; Timing: samples signal AB in every 12cycles.
; Max frequency: 1 change in 12 cycles is allowed and correctly decoded always.

; The program runs in an exact 36 cycle period of which ~24  cycle is to increment/decrement counter, 12 cycle is to communicate.
; There are 3 samples taken in each loop in equal distance thus 1 in every 12 cycles.

; Specification:
; * Decodes Quadrature signal (AB signal) input is counted constantly from 0 at reset. Zeroing is not possible.
; * Decoded Quad signal is a 32 bit counter, accessible through SPI using the following interface:
; ** NCS 1->0 initiates communication as an SPI slave PIN_SPI_CLK is input, PIN_SPI_DATA is set to otput mode
; ** between sending bytes a short timeout is necessary - TODO configure so that the receiver of the data can safely handle it
;     (Designed to be usable from any master uC)
; ** 4 counter bytes are sent. Least significant byte first. Least significant bit first.
; ** SCK negative edge: set data. SCK positive edge: sample data line. Communication starts with positive edge.
; ** 1 byte error is send. non-0 means an error code: signals overflown since last communication. error flag is cleared after being sent.
; ** (NCS 0->1 cancels communication: PIN_SPI_CLK and PIN_SPI_DATA are set to input mode, SPI sending is reset - current 5 bytes are finished!)
; * Communication is never blocked by too many input signals.
; * Readout takes 92 big cycles = 3312 CPU cycles = 207 us (Without additional wait cycles - they may be necessary)
; * After CLK up edge we have 4 big cycles to set up receiving the next byte. After 4 cycles we receive the next up edge on the clock line. 4 cycles means 144 CPU clock cycles.

; HW pinout:
;			NRESET	-|1	8|- VCC
;	SPI_DATA	PB3	-|2	7|- PB2 Input	Quad SignalA 
;	SPI_CLK		PB4	-|3	6|- PB1 SPI_NCS
;			GND	-|4	5|- PB0 Input Quad SignalB
; All pins are high-Z input by default. Pullup is not applied.
; SPI_CLK and SPI_DATA is turned output for 5 bytes SPI output after SPI_NCS input goes low.

.nolist
.include "tn25def.inc"
.list

.equ PIN_NCS = 1	; NCS bit in PINB
.equ PIN_SPI_CLK = 4	; NCS bit in PINB
.equ PIN_SPI_DATA = 3	; NCS bit in PINB

; Registers used by communication
.def COMM_COUNTER32_0 = r20	; Copy of Q32 latched for sending
.def COMM_COUNTER32_1 = r21
.def COMM_COUNTER32_2 = r22
.def COMM_COUNTER32_3 = r23
.def COMMUNICATION_STATE = r24	; State machine state. Pointer to the state handler within the low 256 addresses.

; The internal counter
.def COUNTER32_0 = r26
.def COUNTER32_1 = r27
.def COUNTER32_2 = r28
.def COUNTER32_3 = r29
.def COUNTER_ERROR = r17	; Error is set to 1 in case of error in quad decoding. Zeroed after readout.
; .def ZL = r30

; Samples of PINB stored for later processing
.def PRSAMPLE0 = r10 ; Oldest sample - Last sample of previous processing
.def PRSAMPLE1 = r11 ; Old sample - First sample taken in this cycle
.def PRSAMPLE2 = r12 ; Less old sample. - Second sample taken in this cycle. ZL stores the last sample taken in this cycle.

; Constants for cases when intermediate can not be used (eor, out)
.def CONST_ZERO = r0
.def CONST_MASK = r16
.def CONST_SPI_MASK = r1

; States of Byte shifting bit-by-bit (SPI like protocol)
.def BYTESHIFT_N = r18		; Counter of remaining bits to shift out in this byte
.def BYTESHIFT_VALUE = r19	; Current value to be shifted out in this byte. Value is shifted as a bit was sent out
.def BYTESHIFT_RET = r25	; Return state is stored here. COMMUNICATION_STATE is set to this value when byte shift was finished

.CSEG
.org 0x0000
;Interrupt vector table - No interrupts are used so we simply start our program here
reset:
	ldi ZH, (1<<PIN_SPI_CLK)|(1<<PIN_SPI_DATA)
	mov CONST_SPI_MASK, ZH
	LDI ZH, 0
	mov CONST_ZERO, ZH
	mov COUNTER32_0, ZH
	mov COUNTER32_1, ZH
	mov COUNTER32_2, ZH
	mov COUNTER32_3, ZH

	ldi ZH, 0x01	; ZH is used with this constant value
	ldi COMMUNICATION_STATE, low(COMM_STATE_OFF)	; Initial communication state is OFF
	ldi COUNTER_ERROR, 0
	ldi CONST_MASK, 0b00000101	; Mask to find the signal AB bits

	in PRSAMPLE0, PINB		; Initialize previous samples before first normal cycle
	and PRSAMPLE0, CONST_MASK	; PRSAMPLE0 is always stored already masked format!
	in PRSAMPLE1, PINB		; Initialize previous samples before first normal cycle
	in PRSAMPLE2, PINB		; Initialize previous samples before first normal cycle
loop:		; In every N cycle a sample is taken
	in ZL, PINB

; Process 4 consecutive samples with 3 possible increments. After reading PRSAMPLE0 the latest sample is stored into PRSAMPLE0
process3samples:
	; Prepare jump value: combine 4*2 sample into a single byte that is a jumptable address
	; and PRSAMPLE0, CONST_MASK ALREADY MASKED!
	and PRSAMPLE1, CONST_MASK
	and PRSAMPLE2, CONST_MASK
	and ZL, CONST_MASK

	lsl PRSAMPLE1
	or PRSAMPLE1, PRSAMPLE0
	mov PRSAMPLE0, ZL		; Store last sample of this processing cycle so it is available in next cycle

	swap PRSAMPLE1
	lsl PRSAMPLE2
	or ZL, PRSAMPLE2
	or ZL, PRSAMPLE1
	ldi ZH, 1
sample1:
	in PRSAMPLE1, PINB		; (Jump value prepared) We are at 12 cycles: read a sample
process3samples_ijmp:
	ijmp	; Jump signal pattern processing table - see quad_jumptable.inc

process3samples_ret:			; After updating the counters we go on with execution
	mov ZL, COMMUNICATION_STATE	; 1 Tablejump based on current communication state
sample2:
	in PRSAMPLE2, PINB		; We are at cycle 24: read a sample
	ldi ZH, 0
	ijmp				; Communication states are at ZH==0x00, ZL are lo(COMM_STATE_xxx)


;;; Jumptable arrives to either of these handlers. Add 0,1,2,3,-1,-2,-3 to the counter or mark error state:
process_unchanged:			; Count 0
	nop				; NOPs so this branch takes same time as others
	nop
	nop
	nop
	rjmp process3samples_ret
process_error:				; Mark error due to signal overflow
	ldi COUNTER_ERROR, 1		; Signal that there was an error
	nop				; NOPs so this branch takes same time as others
	nop
	nop
	rjmp process3samples_ret
process_inc1:				; Count +1
	subi COUNTER32_0, -1
	sbci COUNTER32_1, 0xff
	sbci COUNTER32_2, 0xff
	sbci COUNTER32_3, 0xff
	rjmp process3samples_ret
process_inc2:				; Count +2
	subi COUNTER32_0, -2
	sbci COUNTER32_1, 0xff
	sbci COUNTER32_2, 0xff
	sbci COUNTER32_3, 0xff
	rjmp process3samples_ret
process_inc3:				; Count +3
	subi COUNTER32_0, -3
	sbci COUNTER32_1, 0xff
	sbci COUNTER32_2, 0xff
	sbci COUNTER32_3, 0xff
	rjmp process3samples_ret
process_dec1:				; Count -1
	subi COUNTER32_0, 1
	sbci COUNTER32_1, 0
	sbci COUNTER32_2, 0
	sbci COUNTER32_3, 0
	rjmp process3samples_ret
process_dec2:				; Count -2
	subi COUNTER32_0, 2
	sbci COUNTER32_1, 0
	sbci COUNTER32_2, 0
	sbci COUNTER32_3, 0
	rjmp process3samples_ret
process_dec3:				; Count -3
	subi COUNTER32_0, 3
	sbci COUNTER32_1, 0
	sbci COUNTER32_2, 0
	sbci COUNTER32_3, 0
	rjmp process3samples_ret


; Communication states:
COMM_STATE_OFF:	; OFF - See if comm is initiated otherwise keep SPI off
	SBRS PRSAMPLE2, PIN_NCS
	ldi COMMUNICATION_STATE, low(COMM_STATE_START_BY_NCS)
	out DDRB, CONST_ZERO
	out PORTB, CONST_ZERO
	nop
	nop
	rjmp loop

COMM_STATE_START_BY_NCS:	; Communication is started by pulling NCS
	ldi ZL, (1<<PIN_SPI_CLK) | (0<<PIN_SPI_DATA)
	out PORTB, ZL
	out DDRB, CONST_SPI_MASK
	ldi COMMUNICATION_STATE, low(COMM_STATE_START)
	nop
	nop
	rjmp loop

COMM_STATE_START:	; START - store current value
	mov	COMM_COUNTER32_0, COUNTER32_0
	mov	COMM_COUNTER32_1, COUNTER32_1
	mov	COMM_COUNTER32_2, COUNTER32_2
	mov	COMM_COUNTER32_3, COUNTER32_3
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTE_0)
	nop
	rjmp loop

COMM_STATE_BYTE_0:	; Send byte 0
	mov BYTESHIFT_VALUE, COMM_COUNTER32_0
	ldi BYTESHIFT_N, 8
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_1)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA)
	nop
	nop
	rjmp loop

COMM_STATE_BYTE_1:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_1
	ldi BYTESHIFT_N, 8
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_2)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA)
	nop
	nop
	rjmp loop

COMM_STATE_BYTE_2:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_2
	ldi BYTESHIFT_N, 8
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_3)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA)
	nop
	nop
	rjmp loop

COMM_STATE_BYTE_3:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_3
	ldi BYTESHIFT_N, 8
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_4)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA)
	nop
	nop
	rjmp loop

COMM_STATE_BYTE_4:
	mov BYTESHIFT_VALUE, COUNTER_ERROR
	ldi COUNTER_ERROR, 0
	ldi BYTESHIFT_N, 8
	ldi BYTESHIFT_RET, low(COMM_STATE_FINISHED)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA)
	nop
	rjmp loop

COMM_STATE_FINISHED:
	out PORTB, CONST_ZERO	; Release SCK and DATA lines
	out DDRB, CONST_ZERO
	ldi COMMUNICATION_STATE, low(COMM_STATE_OFF)
	SBRS PRSAMPLE2, PIN_NCS
	ldi COMMUNICATION_STATE, low(COMM_STATE_FINISHED)
	nop
	rjmp loop

COMM_STATE_BYTESHIFT_DATA:	; Clock to low, data to output
	ldi ZL, (1<<PIN_SPI_CLK) | (0<<PIN_SPI_DATA)
	SBRC BYTESHIFT_VALUE, 0
	ldi ZL, (1<<PIN_SPI_CLK) | (1<<PIN_SPI_DATA)
	OUT PORTB, ZL
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_CLK)
	lsr BYTESHIFT_VALUE
	rjmp loop

COMM_STATE_BYTESHIFT_CLK:	; Clock strobe
	CBI PORTB, PIN_SPI_CLK
	dec BYTESHIFT_N		; dec also updates the SREG
	BRNE COMM_STATE_BYTESHIFT_CLK_NEXT
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA_END)
	nop
	rjmp loop

COMM_STATE_BYTESHIFT_CLK_NEXT:
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA)
	rjmp loop

COMM_STATE_BYTESHIFT_DATA_END:
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA_END2)
	nop
	nop
	nop
	nop
	nop
	rjmp loop
COMM_STATE_BYTESHIFT_DATA_END2:
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA_END3)
	nop
	nop
	nop
	nop
	nop
	rjmp loop
COMM_STATE_BYTESHIFT_DATA_END3:
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA_END4)
	nop
	nop
	nop
	nop
	nop
	rjmp loop
COMM_STATE_BYTESHIFT_DATA_END4:
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA_END5)
	nop
	nop
	nop
	nop
	nop
	rjmp loop
COMM_STATE_BYTESHIFT_DATA_END5:
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_DATA_END_RET)
	nop
	nop
	nop
	nop
	nop
	rjmp loop

COMM_STATE_BYTESHIFT_DATA_END_RET:
	mov COMMUNICATION_STATE, BYTESHIFT_RET
	nop
	nop
	nop
	nop
	nop
	rjmp loop
CODE_ENDS:

.nolist
.include "quad_jumptable.inc"
.list	; "quad_jumptable.inc" is hidden from the list output

