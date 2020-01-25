; Quadrature decoder - totally optimized version. TODO never executed - just a proof of concept
; Using raw ASM - compiles with avra - instead of avr-gcc allows
; us to place ISR handling code directly into the ISR table thus sparing 2 cycles (rjmp) on each ISR
; This also disables using the higher indexed ISRs but we don't use them in this application.

; Specification:
; * Decodes Quadrature signal (AB signal) with about 20 CPU clock cycles maximum processing time of each change of signal A
;    (Only changes in signal A generate interrupt so it is inherently twice faster than solutions interrupting on both signals)
; * Decoded Quad signal is a 32 bit counter, accessible through SPI using the following interface:
; ** NCS 1->0 initiates communication PIN_SPI_CLK and PIN_SPI_DATA are set to otput mode
; ** When communicating SW SPI master mode is implemented:
; ** First byte is sent at once, then iterate next bytes
; ** between sending bytes there is a short timeout - TODO configure so that the receiver of the data can safely handle it
;     (Designed to be usable from master uC that processes bits by HW and processes each byte by ISR or polling SW - Just like ATMega)
; ** NCS 0->1 cancels communication: PIN_SPI_CLK and PIN_SPI_DATA are set to input mode, SPI sending is reset
; Data Receiver must implement a timeout for the communication: in case the signal A interrupts are too frequent then
;  communication fails because that is executed on main thread.
;  Even in this case the pins are set to input mode and communication is cancelled. So the implementation prevents sending invalid data!

; HW:
;			NRESET	-|1	8|- VCC
;	Input	QuadA	PB3	-|2	7|- PB2 SPI_CLK - connect to SPI bus throgh a resistor so main processor can sense and override
;	Input	QuadB	PB4	-|3	6|- PB1 SPI_DATA - connect to SPI bus throgh a resistor so main processor can sense and override
;			GND	-|4	5|- PB0 SPI_NCS

.nolist
.include "tn25def.inc"
.list

.equ BIT_NCS = 1	; NCS bit in PINB
.equ BIT_SPI_CLK = 1	; NCS bit in PINB
.equ BIT_SPI_DATA = 1	; NCS bit in PINB

; Registers used in ISR - not allowed anywhere else outside cli/sei block
.def ISR_SREG = r1		; Save SREG
.def ISR_1 = r2			; Temporary storage within ISR
.def ISR_QUAD_PREV = r3		; value of PINB (QUAD encoder) as it was read in last ISR cycle
.def ISR_COUNTER16_L = r24	; 16 bit forward/backward counter updated by ISR.
				; This counts on every change of signal A
				; So it does not have the last bit of the final precision
.def ISR_COUNTER16_H = r25

; Registers used in queryValue16
.def Q16_PINB = r4			; current PINB
.def Q16_PREV = r5			; PINB when last ISR executed
.def Q16_COUNTER16_L = r26 		; return value is stored here
.def Q16_COUNTER16_H = r27 		; return value is stored here


; Registers used in queryValue32
.def Q32_COUNTER32_0 = r28 		; Current 32 bit value LSB
.def Q32_COUNTER32_1 = r29 		; Current 32 bit value
.def Q32_COUNTER32_2 = r30 		; Current 32 bit value
.def Q32_COUNTER32_3 = r31 		; Current 32 bit value MSB
.def Q32_DIFF_L = r10
.def Q32_DIFF_H = r11
.def Q32_TEMP = r16

; Registers used in communication
.def COMM_TMP = r17		; Temporary storage

.def COMM_COUNTER32_0 = r20	; Copy of Q32 latched for sending
.def COMM_COUNTER32_1 = r21
.def COMM_COUNTER32_2 = r22
.def COMM_COUNTER32_3 = r23

.CSEG
.org 0x0000
;Interrupt vector table
	rjmp reset
	reti
	reti
	reti
PCINT0_vect:
	in ISR_SREG, SREG		; Save SREG
	in  ISR_1, PINB			; Input current PINB values: signal A and B are interesting
	mov ISR_QUAD_PREV, ISR_1	; Store the current readout value to a persistent register
	LSR ISR_1			; Shift the value so that the A and B signals can be XOR-ed
	eor ISR_1, ISR_QUAD_PREV	; xor the two signal bits A and B (all other bits are ignored)
	SBRS ISR_1, 1 			; branch depending on A XOR B - increment or decrement counter
	rjmp ISR_INC
ISR_DEC:
	adiw ISR_COUNTER16_L, 1		; Increment Quad counter
	out SREG, ISR_SREG		; Restore SREG
	reti
ISR_INC:
	sbiw ISR_COUNTER16_L, 1			; Decrement Quad counter
	ret
	out SREG, ISR_SREG	; Restore SREG
	SBIS PINB, BIT_NCS	; NCS high: communication cancelled - we chack it in ISR because in case there is an ISR overload
				; That may corrupt communication. By cancelling communication the receiver can timeout but no
				; corrupt data is received
	reti
	cbi DDRB, BIT_SPI_CLK	; Disable output on clock pin
	cbi DDRB, BIT_SPI_DATA	; Disable output on SPI output pin
	reti

reset:
	; TODO activate PIN change interrupt for signal A
	rjmp PCINT0_vect	; Initialize the current state of the counter subsystem
	cli			; reti of PCINT0_vect also does sei - maybe PCINT0_vect may be executed twice
	ldi ISR_COUNTER16_L, 0  ; Zero ISR_COUNTER16 counter
	ldi ISR_COUNTER16_H, 0
	sei			; Internal counter works in ISR
loop:
	rcall queryValue32	; Periodically update the 32 bit counter so the ISR_COUNTER16 never over turns around twice
	SBIS PINB, BIT_NCS	; NCS low: communication initiated
	rcall commOnce
	rjmp loop

queryValue16: ; Query the current counter value from the main thread: always correct but ISR processing time is increased
	cli	; Disable interrputs for the time of read out. This increases ISR processing time with 6-7 cycles!
	MOVW Q16_COUNTER16_L, ISR_COUNTER16_L	; read out counter
	mov Q16_PREV,ISR_QUAD_PREV		; read out latest PINB value - may not eq to current pinb
	in Q16_PINB,PINB	; read out current PINB value
	sei
	; TODO multiply QUERY_COUNTER16 by 2
	; TODO update QUERY_COUNTER16_L - 1 more bit is possible to be gained by updating based on QTEMP_PINB and QTEMP_PREV
	ret

refresh:	; This has to be called periodically to refresh self state
queryValue32: ; Query the current 32 bit counter value: updates the QUERY_COUNTER32 bytes so that they reflect the latest current value
	rcall queryValue16

	; diff=QUERY_COUNTER16-lo16(QUERY_COUNTER32) = new - old
	mov Q32_DIFF_L, Q16_COUNTER16_L
	mov Q32_DIFF_H, Q16_COUNTER16_H
	sub Q32_DIFF_L, Q32_COUNTER32_0 ; Subtract low byte
	sbc Q32_DIFF_H, Q32_COUNTER32_1 ; Subtract with carry high byte
	
	; Was there overflow or underflow since last update?
	SBRS Q32_DIFF_H, 7	; Skip if <0 (highest bit is 1)
	rjmp q32_diff_non_neg	; diff>=0
q32_diff_neg:			; diff<0 && new>old -> underflow -> dec upper bytes
	cp  Q32_DIFF_L, Q16_COUNTER16_L
	cpc Q32_DIFF_H, Q16_COUNTER16_H
	brlo q32_overflow_done
	ldi Q32_TEMP, 1
	add Q32_COUNTER32_2, Q32_TEMP
	ldi Q32_TEMP, 0
	adc Q32_COUNTER32_3, Q32_TEMP

	rjmp q32_overflow_done
q32_diff_non_neg:		;  diff>0 && new<old -> overflow -> inc upper bytes
	cp  Q16_COUNTER16_L, Q32_DIFF_L
	cpc Q16_COUNTER16_H, Q32_DIFF_H
	brlo q32_overflow_done
	ldi Q32_TEMP, 0xff
	add Q32_COUNTER32_2, Q32_TEMP
	adc Q32_COUNTER32_3, Q32_TEMP


q32_overflow_done:
	mov Q32_COUNTER32_0, Q16_COUNTER16_L	; After inc/dec of higher bytes overwrite Q32 counter low bytes with current readout of counter
	mov Q32_COUNTER32_1, Q16_COUNTER16_H
	ret

commOnce:			; Send current 32 bit value through SPI
	mov COMM_COUNTER32_0, Q32_COUNTER32_0	; Latch current value of 32 bit counter
	mov COMM_COUNTER32_1, Q32_COUNTER32_1
	mov COMM_COUNTER32_2, Q32_COUNTER32_2
	mov COMM_COUNTER32_3, Q32_COUNTER32_3

	; TODO enter output mode
	rcall commOnceOutputMode
	; TODO cancel output mode and reset sending state
	ret

commOnceOutputMode:
	; TODO configure SPI HW
	; TODO Set data out byte0
	mov COMM_TMP, COMM_COUNTER32_0
	rcall SPITransfer
	rcall comm_wait		; Wait some time so master can process the received value

	SBIC PINB, BIT_NCS	; NCS high: communication cancelled
	ret
	SBIS DDRB, BIT_SPI_CLK	; CLK cleared by ISR: communication cancelled
	ret

	mov COMM_TMP, COMM_COUNTER32_1
	rcall SPITransfer
	rcall comm_wait		; Wait some time so master can process the received value

	SBIC PINB, BIT_NCS	; NCS high: communication cancelled
	ret
	SBIS DDRB, BIT_SPI_CLK	; CLK cleared by ISR: communication cancelled
	ret

	mov COMM_TMP, COMM_COUNTER32_2
	rcall SPITransfer
	rcall comm_wait		; Wait some time so master can process the received value

	SBIC PINB, BIT_NCS	; NCS high: communication cancelled
	ret
	SBIS DDRB, BIT_SPI_CLK	; CLK cleared by ISR: communication cancelled
	ret

	mov COMM_TMP, COMM_COUNTER32_3
	rcall SPITransfer
	ret


	; Wait for byte send:
comm_wait:
	rcall queryValue32	; Querying 32 bit value periodically is required to keep the 32 bit counter synchronized
	SBIC PINB, BIT_NCS	; NCS high: communication cancelled
	ret
	SBIS DDRB, BIT_SPI_CLK	; CLK cleared by ISR: communication cancelled
	ret

	; TODO cancel wait on some event - use timer?
	rjmp comm_wait
	ret
	
SPITransfer:
	rcall SPI_Transfer_bit
	lsl COMM_TMP
	rcall SPI_Transfer_bit
	lsl COMM_TMP
	rcall SPI_Transfer_bit
	lsl COMM_TMP
	rcall SPI_Transfer_bit
	lsl COMM_TMP
	rcall SPI_Transfer_bit
	lsl COMM_TMP
	rcall SPI_Transfer_bit
	lsl COMM_TMP
	rcall SPI_Transfer_bit
	lsl COMM_TMP
	rcall SPI_Transfer_bit
	ret

SPI_Transfer_bit:		; SW SPI transfer that periodically checks if transfer was cancelled
	SBIC PINB, BIT_NCS	; NCS high: communication cancelled
	ret
	SBIS DDRB, BIT_SPI_CLK	; CLK cleared by ISR: communication cancelled
	ret

	SBRS COMM_TMP, 0	; Test current bit
	rjmp SPI_Transfer_bit_low
	sbi PORTB, BIT_SPI_DATA ; Set data to high if high bit
SPI_Transfer_bit_low:
	cbi PORTB, BIT_SPI_DATA ; Set data to low if low bit
	sbi PORTB, BIT_SPI_CLK ; Set clk to high
	cbi PORTB, BIT_SPI_CLK ; Set clk to low
	ret



