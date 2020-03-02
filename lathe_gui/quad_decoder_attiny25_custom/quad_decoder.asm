; Quadrature decoder - totally optimized version. Tested in simulator and using signal generator: works as expected.
; Using raw ASM - compiles with avra - instead of avr-gcc
; The program does not use ISRs
; Timing: samples signal AB in every 12cycles.
; Max frequency: 1 change in 12 cycles is allowed and correctly decoded always.

; The program runs in an exact 2*36 cycle big period of which ~36  cycle is to increment/decrement counter, 12 cycle is to communicate.
; There are 2*3 samples taken in each loop in equal distance thus 1 in every 12 cycles.

; Specification:
; * Decodes Quadrature signal (AB signal) input is counted always from 0 at reset. Zeroing is not possible.
; * Decoded Quad signal is a 32 bit counter, accessible through the following custom interface:
; ** COMM line is pulled up externally by 10kOhm and is connected to master through 400Ohm (limiting current to about 10mA in case of driving the two sides against each other. This is only possible in case of an error.)
; ** NCS 1->0->1(released - external pullup only) strobe initiates communication. Length of the strobe must be at least 1 big period (72 clock cycles).
; ** Communication is started in 1-2-3 big periods
; ** When communication is ongoing this MCU drives the COMM line. MCU sends all data in a fixed amount of time.
; ** A single bit is sent in a single big period time:
; *** Comm is driven to low
; *** In case of value 1 Comm is driven to high after 1/3 of the big period
; *** In case of value 0 Comm is driven to high after 2/3 of the big period
; ** Bits of a byte are sent without additional big periods between them
; ** After each byte there is a single wait big period
; ** 4 counter bytes are sent. Least significant byte first. Least significant bit first.
; ** 1 byte status is sent. Bitmask meaning:
; *** 1: signals overflown since last communication. flag is cleared after being sent.
; *** 2: zero signal was received since last communication. Flag is cleared after being sent.
; * Communication is never blocked by too many input signals.
; * After communication the COMM line is released by the MCU and is waiting for the next query

; HW pinout:
;			NRESET	-|1	8|- VCC
;	NZERO_IN 	PB3	-|2	7|- PB2 Input	Quad SignalA 
;			PB4	-|3	6|- PB1 COMM
;			GND	-|4	5|- PB0 Input Quad SignalB
; All pins are high-Z input by default. Pullup is not applied.
; SPI_CLK and SPI_DATA is turned output for 5 bytes SPI output after SPI_NCS input goes low.

.nolist
.include "tn25def.inc"
.list

.equ PIN_COMM = 1	; index of COMM bit in PINB
.equ PIN_INDEX_NCS = 1	; index of chip select - can be the same as COMM but for scope debugging sessions it can be set to a separate pin
.equ PIN_ZERO_IN = 3	; ZERO input bit in PINB

.equ COUNTER_STATUS_MASK_ZEROED = 2
.equ COUNTER_STATUS_MASK_ERROR = 1
.equ OUT_MASK_COMM_HIGH = (1<<PIN_COMM)
.equ OUT_MASK_COMM_LOW = 0

; In the stored table this value marks an error in pattern decoding
.equ ERROR_MARKER = 4

; Registers used by communication
.def COMM_COUNTER32_0 = r6	; Copy of 32 bit value latched for sending
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
.def CONST_COMM_HIGH = r1
.def ADD_CYCLE0 = r20
.def ADD_CYCLE1 = r21

; States of Byte shifting bit-by-bit (SPI like protocol)
.def BYTESHIFT_NEXT = r22	; Value to write to PORTA after 1/3 big period
.def BYTESHIFT_N = r18		; Counter of remaining bits to shift out in this byte
.def BYTESHIFT_VALUE = r19	; Current value to be shifted out in this byte. Value is shifted as a bit was sent out
.def BYTESHIFT_RET = r25	; Return state is stored here. COMMUNICATION_STATE is set to this value when byte shift was finished

.CSEG
.org 0x0000
;Interrupt vector table - No interrupts are used so we simply start our program here
reset:
	LDI ZH, OUT_MASK_COMM_HIGH
	mov CONST_COMM_HIGH, ZH
	LDI ZH, 0
	mov CONST_ZERO, ZH
	mov COUNTER32_0, ZH
	mov COUNTER32_1, ZH
	mov COUNTER32_2, ZH
	mov COUNTER32_3, ZH
	mov ZERO_0, ZH
	mov ZERO_1, ZH
	mov ZERO_2, ZH
	mov ZERO_3, ZH

	ldi COMMUNICATION_STATE, low(COMM_STATE_OFF)	; Initial communication state is OFF
	ldi COUNTER_STATUS, 0
	ldi CONST_MASK, 0b00000101	; Mask to find the signal AB bits

	in PRSAMPLE0, PINB		; Initialize previous samples before first normal cycle
	and PRSAMPLE0, CONST_MASK	; PRSAMPLE0 is always stored already masked format!
	in PRSAMPLE1, PINB		; Initialize previous samples before first normal cycle
	in PRSAMPLE2, PINB		; Initialize previous samples before first normal cycle
	ldi ZH, 0b10			; ZH is 0b10. LPM targets 0x100 and ijmp targets 0x200
sample0a:
comm_read:	; Ideal read time for communication sample
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

	ldi BYTESHIFT_NEXT, OUT_MASK_COMM_HIGH  ; Reset BYTESHIFT_NEXT value after used
sample1a:
	in PRSAMPLE1, PINB	; We are at 12 cycles: read a sample
	out PORTB, CONST_COMM_HIGH
process3samples_a:
	lpm ADD_CYCLE0, Z			; Cycles: 3
	sbrc PRSAMPLE1, PIN_ZERO_IN		; Do not update zero reg if not
	rjmp no_zero
	movw ZERO_0, COUNTER32_0
	movw ZERO_2, COUNTER32_2
	sbr COUNTER_STATUS, COUNTER_STATUS_MASK_ZEROED
no_zero_ret:
	nop
	mov ZL, COMMUNICATION_STATE
sample2a:
	in PRSAMPLE2, PINB
	ijmp			; Jump to communication state machine: 6 useful cycles

no_zero:
	rjmp no_zero_ret
comm_ret:
	nop
	nop
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
	out PORTB, BYTESHIFT_NEXT
	add COUNTER32_0, ADD_CYCLE0
	adc COUNTER32_1, ADD_CYCLE1
	adc COUNTER32_2, ADD_CYCLE1
	adc COUNTER32_3, ADD_CYCLE1
	; 4 spare cycles
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
	out PORTB, BYTESHIFT_NEXT
	sbr COUNTER_STATUS, COUNTER_STATUS_MASK_ERROR
	nop
	nop
	; 5 spare cycles
	nop
	nop
	nop
	nop
	nop
	rjmp loop
FIRST_256_LAST:

.org 0x100
FIRST_256_ENDS:

.nolist
.include "quad_jumptable.inc"
.list	; "quad_jumptable.inc" is hidden from the list output

; Communication states:

.org 0x200
COMM_STATE_OFF:	; OFF - See if comm is initiated otherwise keep COMMunication off
	SBRS PRSAMPLE2, PIN_INDEX_NCS
	ldi COMMUNICATION_STATE, low(COMM_STATE_START_BY_NCOMM)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_START_BY_NCOMM:	; Communication is started by pulling NCOMM to 0. Wait until released
	SBRC PRSAMPLE2, PIN_INDEX_NCS
	ldi COMMUNICATION_STATE, low(COMM_STATE_START)
	nop
	nop
	nop
	rjmp comm_ret

COMM_STATE_START:	; START - store current value
	movw	COMM_COUNTER32_0, COUNTER32_0
	movw	COMM_COUNTER32_2, COUNTER32_2
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTE_0)
	out PORTB, CONST_COMM_HIGH	; Drive COMM line
	out DDRB, CONST_COMM_HIGH
	rjmp comm_ret

COMM_STATE_BYTE_0:	; Send byte 0
	mov BYTESHIFT_VALUE, COMM_COUNTER32_0
;	ldi BYTESHIFT_VALUE, 0b10101010
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_1)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_0)
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_1:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_1
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_2)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_0)
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_2:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_2
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_3)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_0)
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_3:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_3
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_4)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_0)
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_4:
	mov BYTESHIFT_VALUE, COUNTER_STATUS
	ldi COUNTER_STATUS, 0
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_5)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_0)
	nop
	rjmp comm_ret

COMM_STATE_BYTE_5:	; ZERO - store current value
	movw	COMM_COUNTER32_0, ZERO_0
	movw	COMM_COUNTER32_2, ZERO_2
	mov BYTESHIFT_VALUE, COMM_COUNTER32_0
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_6)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_0)
	rjmp comm_ret

COMM_STATE_BYTE_6:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_1
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_7)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_0)
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_7:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_2
	ldi BYTESHIFT_RET, low(COMM_STATE_BYTE_8)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_0)
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTE_8:
	mov BYTESHIFT_VALUE, COMM_COUNTER32_3
	ldi BYTESHIFT_RET, low(COMM_STATE_FINISHED)
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_0)
	nop
	nop
	rjmp comm_ret

COMM_STATE_FINISHED:
	out DDRB, CONST_ZERO
	out PORTB, CONST_ZERO	; Release all lines
	ldi COMMUNICATION_STATE, low(COMM_STATE_OFF)
	nop
	nop
	rjmp comm_ret

COMM_STATE_BYTESHIFT_0:
	out PORTB, CONST_ZERO ; Pull to 0
	ldi BYTESHIFT_NEXT, 0
	sbrs BYTESHIFT_VALUE, 0
	ldi BYTESHIFT_NEXT, OUT_MASK_COMM_HIGH
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_1)
	rjmp comm_ret

COMM_STATE_BYTESHIFT_1:
	out PORTB, CONST_ZERO ; Pull to 0
	ldi BYTESHIFT_NEXT, 0
	sbrs BYTESHIFT_VALUE, 1
	ldi BYTESHIFT_NEXT, OUT_MASK_COMM_HIGH
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_2)
	rjmp comm_ret

COMM_STATE_BYTESHIFT_2:
	out PORTB, CONST_ZERO ; Pull to 0
	ldi BYTESHIFT_NEXT, 0
	sbrs BYTESHIFT_VALUE, 2
	ldi BYTESHIFT_NEXT, OUT_MASK_COMM_HIGH
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_3)
	rjmp comm_ret

COMM_STATE_BYTESHIFT_3:
	out PORTB, CONST_ZERO ; Pull to 0
	ldi BYTESHIFT_NEXT, 0
	sbrs BYTESHIFT_VALUE, 3
	ldi BYTESHIFT_NEXT, OUT_MASK_COMM_HIGH
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_4)
	rjmp comm_ret

COMM_STATE_BYTESHIFT_4:
	out PORTB, CONST_ZERO ; Pull to 0
	ldi BYTESHIFT_NEXT, 0
	sbrs BYTESHIFT_VALUE, 4
	ldi BYTESHIFT_NEXT, OUT_MASK_COMM_HIGH
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_5)
	rjmp comm_ret

COMM_STATE_BYTESHIFT_5:
	out PORTB, CONST_ZERO ; Pull to 0
	ldi BYTESHIFT_NEXT, 0
	sbrs BYTESHIFT_VALUE, 5
	ldi BYTESHIFT_NEXT, OUT_MASK_COMM_HIGH
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_6)
	rjmp comm_ret

COMM_STATE_BYTESHIFT_6:
	out PORTB, CONST_ZERO ; Pull to 0
	ldi BYTESHIFT_NEXT, 0
	sbrs BYTESHIFT_VALUE, 6
	ldi BYTESHIFT_NEXT, OUT_MASK_COMM_HIGH
	ldi COMMUNICATION_STATE, low(COMM_STATE_BYTESHIFT_7)
	rjmp comm_ret
COMM_STATE_BYTESHIFT_7:
	out PORTB, CONST_ZERO ; Pull to 0
	ldi BYTESHIFT_NEXT, 0
	sbrs BYTESHIFT_VALUE, 7
	ldi BYTESHIFT_NEXT, OUT_MASK_COMM_HIGH
	mov COMMUNICATION_STATE, BYTESHIFT_RET
	rjmp comm_ret

THIRD_256_ENDS:
.org 0x300

