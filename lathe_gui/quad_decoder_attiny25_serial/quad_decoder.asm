; Quadrature decoder - totally optimized version. NOT TESTED in real.
; Using raw ASM - compiles with avra - instead of avr-gcc
; The program does not use ISRs
; Timing: samples signal AB in every 12cycles.
; Max frequency: 1 change in 12 cycles is allowed and correctly decoded always.

; The program runs in an exact 72 cycle big period
; There are 6 samples taken in each loop in equal distance thus 1 in every 12 cycles.

; Specification:
; * Decodes Quadrature signal (AB signal) input is counted constantly from 0 at reset. Zeroing is not possible.
; * Decoded Quad signal is a 32 bit counter, accessible through SPI using the following interface:
; ** NCS 1->0 initiates communication as an SERIAL output using big cycle as baud
; ** 1 byte error is send. non-0 means an error code: signals overflown since last communication. error flag is cleared after being sent.
; ** (NCS 0->1 cancels communication: PIN_SPI_CLK and PIN_SPI_DATA are set to input mode, SPI sending is reset - current 5 bytes are finished!)
; * Communication is never blocked by too many input signals.
; * Readout takes 92 big cycles = 3312 CPU cycles = 207 us (Without additional wait cycles - they may be necessary)
; * After CLK up edge we have 4 big cycles to set up receiving the next byte. After 4 cycles we receive the next up edge on the clock line. 4 cycles means 144 CPU clock cycles.

; HW pinout:
;			NRESET	-|1	8|- VCC
;	NZERO_IN 	PB3	-|2	7|- PB2 Input	Quad SignalA 
;			PB4	-|3	6|- PB1 SPI_NCS
;			GND	-|4	5|- PB0 Input Quad SignalB
; All pins are high-Z input by default. Pullup is not applied.
; SPI_CLK and SPI_DATA is turned output for 5 bytes SPI output after SPI_NCS input goes low.

.nolist
.include "tn25def.inc"
.list

.equ PIN_NCS = 1	; NCS bit in PINB
.equ PIN_ZERO_IN = 3	; NCS bit in PINB

.equ COUNTER_STATUS_MASK_ZEROED = 2
.equ COUNTER_STATUS_MASK_ERROR = 1
.equ OUT_MASK_NCS = (1<<PIN_NCS)
.equ OUT_MASK_NO_NCS = 0

.equ ERROR_MARKER = 4

; Registers used by communication
.def COMM_COUNTER32_0 = r6	; Copy of Q32 latched for sending
.def COMM_COUNTER32_1 = r7
.def COMM_COUNTER32_2 = r8
.def COMM_COUNTER32_3 = r9
.def COMMUNICATION_STATE = r24	; State machine state. Pointer to the state handler within the low 256 addresses.

; The internal counter
.def COUNTER32_0 = r26
.def COUNTER32_1 = r27
.def COUNTER32_2 = r28
.def COUNTER32_3 = r29
.def COUNTER_STATUS = r17	; Status register of the counter zeroed after readout.
; .def ZL = r30
.def ZERO_0 = r2
.def ZERO_1 = r3
.def ZERO_2 = r4
.def ZERO_3 = r5

; Samples of PINB stored for later processing
.def PRSAMPLE0 = r10 ; Oldest sample - Last sample of previous processing
.def PRSAMPLE1 = r11 ; Old sample - First sample taken in this cycle
.def PRSAMPLE2 = r12 ; Less old sample. - Second sample taken in this cycle. ZL stores the last sample taken in this cycle.

; Constants for cases when intermediate can not be used (eor, out)
.def CONST_ZERO = r0
.def CONST_MASK = r16
.def ADD_CYCLE0 = r20
.def ADD_CYCLE1 = r21

; States of Byte shifting bit-by-bit (SPI like protocol)
.def BYTESHIFT_NEXT = r22
.def BYTESHIFT_N = r18		; Counter of remaining bits to shift out in this byte
.def BYTESHIFT_VALUE = r19	; Current value to be shifted out in this byte. Value is shifted as a bit was sent out
.def BYTESHIFT_RET = r25	; Return state is stored here. COMMUNICATION_STATE is set to this value when byte shift was finished

.CSEG
.org 0x0000
;Interrupt vector table - No interrupts are used so we simply start our program here
reset:
	LDI ZH, 0
	mov CONST_ZERO, ZH
	mov COUNTER32_0, ZH
	mov COUNTER32_1, ZH
	mov COUNTER32_2, ZH
	mov COUNTER32_3, ZH

	ldi ZH, 0x01	; ZH is used with this constant value
	ldi COMMUNICATION_STATE, low(COMM_STATE_OFF)	; Initial communication state is OFF
	ldi COUNTER_STATUS, 0
	ldi CONST_MASK, 0b00000101	; Mask to find the signal AB bits

	in PRSAMPLE0, PINB		; Initialize previous samples before first normal cycle
	and PRSAMPLE0, CONST_MASK	; PRSAMPLE0 is always stored already masked format!
	in PRSAMPLE1, PINB		; Initialize previous samples before first normal cycle
	in PRSAMPLE2, PINB		; Initialize previous samples before first normal cycle
	ldi ZH, 0b10			; ZH is 0b10 by default
sample0a:
loop:		; In every N cycle a sample is taken
	in ZL, PINB
	; Process 5 consecutive samples with 4 possible increments. After reading PRSAMPLE0 the latest sample is stored into PRSAMPLE0
	; Prepare jump value: combine 4*2 sample into a single byte that is a jumptable address
	; and PRSAMPLE0, CONST_MASK ALREADY MASKED!
	and PRSAMPLE1, CONST_MASK
	and PRSAMPLE2, CONST_MASK
	and ZL, CONST_MASK

	lsl PRSAMPLE1
	or PRSAMPLE1, PRSAMPLE0
	mov PRSAMPLE0, ZL

	swap PRSAMPLE1
	lsl PRSAMPLE2
	or ZL, PRSAMPLE2
	or ZL, PRSAMPLE1

	nop
sample1a:
	in PRSAMPLE1, PINB	; We are at 12 cycles: read a sample
process3samples_a:
	lpm ADD_CYCLE0, Z			; Cycles: 3
	sbrc PRSAMPLE1, PIN_ZERO_IN		; Do not update zero reg if not
	rjmp no_zero
	movw ZERO_0, COUNTER32_0
	movw ZERO_2, COUNTER32_2
	sbr COUNTER_STATUS, COUNTER_STATUS_MASK_ZEROED
no_zero_ret:
	ldi ZH, 0	; Prepare comm ijmp
	mov ZL, COMMUNICATION_STATE
	nop
sample2a:
	in PRSAMPLE2, PINB
	ijmp			; Jump to communication state machine: 6 useful cycles

no_zero:
	rjmp no_zero_ret
comm_ret:
	ldi ZH, 0b10			; ZH is 0b10 by default
sample0b:
	in ZL, PINB
	and PRSAMPLE1, CONST_MASK
	and PRSAMPLE2, CONST_MASK
	and ZL, CONST_MASK

	lsl PRSAMPLE1
	or PRSAMPLE1, PRSAMPLE0
	mov PRSAMPLE0, ZL

	swap PRSAMPLE1
	lsl PRSAMPLE2
	or ZL, PRSAMPLE2
	or ZL, PRSAMPLE1
	nop
sample1b:
	in PRSAMPLE1, PINB	; We are at 12 cycles: read a sample
process3samples_b:
	lpm ADD_CYCLE1, Z			; Cycles: 3
	cpi ADD_CYCLE0, ERROR_MARKER
	breq sample_error0
	cpi ADD_CYCLE1, ERROR_MARKER
	breq sample_error1
	add ADD_CYCLE0, ADD_CYCLE1
	ldi ADD_CYCLE1, 255
	sbrs ADD_CYCLE0, 7	; Skip if Negative
	ldi ADD_CYCLE1, 0
sample2b:
	in PRSAMPLE2, PINB
	add COUNTER32_0, ADD_CYCLE0
	adc COUNTER32_1, ADD_CYCLE1
	adc COUNTER32_2, ADD_CYCLE1
	adc COUNTER32_3, ADD_CYCLE1
	; 5 spare cycles
	nop
	nop
	nop
	nop
	nop
	rjmp loop

sample_error0:
	nop
	nop
sample_error1:
	nop
	nop
	nop
sample2b_b:
	in PRSAMPLE2, PINB
	sbr COUNTER_STATUS, COUNTER_STATUS_MASK_ERROR
	nop
	nop
	nop
	; 5 spare cycles
	nop
	nop
	nop
	nop
	nop
	rjmp loop

; Communication states:
COMM_STATE_OFF:	; OFF - See if comm is initiated otherwise keep SPI off
	SBRS PRSAMPLE2, PIN_NCS
	ldi COMMUNICATION_STATE, low(COMM_STATE_START_BY_NCS)
	nop
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_START_BY_NCS:	; Communication is started by pulling NCS. Wait until released
	SBRC PRSAMPLE2, PIN_NCS
	ldi COMMUNICATION_STATE, low(COMM_STATE_START)
	nop
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_START:	; START - store current value
	movw	COMM_COUNTER32_0, COUNTER32_0
	movw	COMM_COUNTER32_2, COUNTER32_2
	ldi COMMUNICATION_STATE, low(COMM_STATE_MEASURE_0)
	nop
	nop
	nop
	rjmp comm_ret


COMM_STATE_MEASURE_0:	; Send measure byte 0
	ldi BYTESHIFT_VALUE, 0b10000000
	ldi BYTESHIFT_RET, low(COMM_STATE_WAIT_MEASURE_0)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_START)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_WAIT_MEASURE_0:
	ldi COMMUNICATION_STATE, low(COMM_STATE_WAIT_MEASURE_1)
	nop
	nop
	nop
	nop
	nop
	rjmp comm_ret
COMM_STATE_WAIT_MEASURE_1:
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTE_0)
	nop
	nop
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_0:	; Send byte 0
	mov BYTESHIFT_VALUE, COMM_COUNTER32_0
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_1)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_START)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_1:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_1
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_2)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_START)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_2:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_2
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_3)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_START)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_3:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_3
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_4)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_START)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_4:
	mov BYTESHIFT_VALUE, COUNTER_STATUS
	ldi COUNTER_STATUS, 0
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_5)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_START)
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_5:	; ZERO - store current value
	movw	COMM_COUNTER32_0, ZERO_0
	movw	COMM_COUNTER32_2, ZERO_2
	mov BYTESHIFT_VALUE, COMM_COUNTER32_0
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_6)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_START)
	nop
	rjmp comm_ret

COMM_STATE_BYTE_6:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_1
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_7)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_START)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_7:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_2
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_8)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_START)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_8:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_3
	ldi BYTESHIFT_RET, low(COMM_STATE_FINISHED)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_START)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_FINISHED:
	out PORTB, CONST_ZERO	; Release all lines
	out DDRB, CONST_ZERO
	ldi COMMUNICATION_STATE, low(COMM_STATE_OFF)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTESHIFT_START:
	ldi BYTESHIFT_N, 9
	ldi BYTESHIFT_NEXT, OUT_MASK_NO_NCS
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_BIT)
	ldi ZL, OUT_MASK_NCS
	out PORTB, ZL
	out DDRB, ZL	; Pull line high before first bit time
	rjmp comm_ret

COMM_STATE_BYTESHIFT_BIT1:
	ldi BYTESHIFT_NEXT, OUT_MASK_NCS
	SBRC BYTESHIFT_VALUE, 0
	ldi BYTESHIFT_NEXT, OUT_MASK_NO_NCS
	lsr BYTESHIFT_VALUE
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_BIT)
	nop
	rjmp comm_ret

COMM_STATE_BYTESHIFT_BIT:	; Clock to low, data to output
	out PORTB, BYTESHIFT_NEXT	; Output proper byteshift value
	nop
	dec BYTESHIFT_N		; dec also updates the SREG
	BRNE COMM_STATE_BYTESHIFT_BIT_NEXT
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_BIT_STOP1)
	nop
	rjmp comm_ret

COMM_STATE_BYTESHIFT_BIT_NEXT:
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_BIT1)
	rjmp comm_ret

COMM_STATE_BYTESHIFT_BIT_STOP1:
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_BIT_STOP2)
	ldi BYTESHIFT_NEXT, OUT_MASK_NCS
	nop
	nop
	nop
	nop
	rjmp comm_ret
COMM_STATE_BYTESHIFT_BIT_STOP2:
	out PORTB, BYTESHIFT_NEXT	; Output proper byteshift value
	mov COMMUNICATION_STATE, BYTESHIFT_RET ; Stop bit must be hold for 2 cycles!
	nop
	nop
	nop
	nop
	rjmp comm_ret
CODE_ENDS:

.nolist
.include "quad_jumptable.inc"
.list	; "quad_jumptable.inc" is hidden from the list output

