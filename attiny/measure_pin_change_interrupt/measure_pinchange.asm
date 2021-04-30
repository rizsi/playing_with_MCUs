; Measure pin change interrupt.
; Using raw ASM - compiles with avra - instead of avr-gcc
; HW pinout:
;			NRESET	-|1	8|- VCC
;  			 PB3	-|2	7|- PB2 debug signal 1
;			PB4	-|3	6|- PB1 pin change interrupt - self driven so the scope image is synchronized
;			GND	-|4	5|- PB0 debug signal 0

.nolist
.include "tn25def.inc"
.list


.CSEG
.org 0x0000
;Interrupt vector table - No interrupts are used so we simply start our program here
	rjmp main
	reti
PCINT0_vect:				; __vector_2 - pin change interrupt
	out PINB, r17
	reti


main:
	ldi r16, 0
	ldi r17, 1
	ldi r18, 0b111
	ldi r19, 0b100
	ldi r21, 0b010


	out PORTB, r16
	out DDRB, r18

	ldi r20, 0b10
	out PCMSK, r20
	ldi r20, 0b00100000
	out GIMSK, r20
	sei
loop:
	OUT PINB, r21
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
	out PINB, r17
rjmp loop

