; Exact cycles wait library

; Exact wait N cycles. Parameter is in r24 - as in avr-gcc calling convention
; rcall, ret and 1 cycle to load the r24 on the caller side is counted.
; So these 2 commands will use exactly 42 cycles:
; ldi r24, 42
; rcall exact_cycles_8
; Minimum cycles that are possible: 20 - less cycles will result in overflow and 256+r24 cycles will be waited

exact_cycles_8:		; we are at 4 cycles because we count "ldi 24, XXX" and "rcall exact_cycles_8"
	lsr r24		; div by 4 - we get the loop count
	brcs add_one_cycle ; Low bit set: +1 cycle
add_one_cycle:
	lsr r24
	brcs add_two_cycle_1 ; 0b10 bit set: +2 cycle
add_two_cycle_1:
	brcs add_two_cycle_2 ; 0b10 bit set: +2 cycle
add_two_cycle_2:
	nop
	nop
	subi r24, 4	; Substract 4(*4) cycles that are wasted counting things. r24 must be at least 1
exact_cycles_8_loop:	; 4 cycles each loop
	dec r24
	nop
	brne exact_cycles_8_loop
	nop		; When we exit the loop after last cycle then that is only 3 cycles

	ret	; 4 cycles

; Exact wait N cycles. Parameter is in r25:r24 pair - as in avr-gcc calling convention
; rcall, ret and 2 cycles to load the r25:r24 on the caller side is counted.
; So these 3 commands will use exactly 0x4242 cycles:
; ldi r25, 0x42
; ldi r24, 0x42
; rcall exact_cycles_16
; Minimum cycles that are possible: 32 (lower values will overflow in the 1 byte arithmetics and will result in 256+r24 wait)
exact_cycles_16:	; we are at 5 cycles because we count "ldi 25, XXX" "ldi 24, XXX" and "rcall exact_cycles_16"
	tst r25		; Check high byte reached 0
	breq r25_zero

	sbiw r25:r24, 128	;	Use 128 cycles until high byte is zero
	mov r23, r24		; Save r24 for call into free to use register
	; 1 loop uses 8 cycles plus these two commands which are accounted by exact_cycles_8:
	ldi r24, 120		; This value plus the cycles used in the loop add up to 128
	rcall exact_cycles_8
	mov r24, r23		; Restore r24 after call
	rjmp exact_cycles_16	; 2 cycles
r25_zero:			; Use cycles remained in low byte
	; All other code uses 12 cycles when entering with r25==0. These 2 commands are counted by exact_cycles_8
	subi r24, 12
	rcall exact_cycles_8

	ret	; 4 cycles

; Exact wait N cycles. Parameter is in r25:r24:r23:r22 - as in avr-gcc calling convention
exact_cycles_32:	; we are at 7 cycles because we count 4 "ldi rYY XXX" and "rcall exact_cycles_32"
	cp r23, ZERO
	cpc r24, ZERO
	cpc r25, ZERO
	breq high24_zero	; Check if high 3 bytes are zero?

	sbiw r23:r22, 128	; Waste 128 cycles in one loop
	sbci r24, 0
	sbci r25, 0
	mov r21, r24		; Save r24 into clobberable register
	ldi r24, TODO_EXACT_VALUE
	rcall exact_cycles_8
	mov r24, r21
high24_zero:			; Use cycles remained in low byte
	TODO substract correct value
	rcall exact_cycles_8

	ret	; 4 cycles


; Different implementation of 1 byte value wait: lower the minimum wait cycles possible
exact_cycles_2_8:	; 4 cycles
	; At least 16 cycles are used in this configuration: we can handle 16-20 cycles additionally which is not a huge win
	cpi r24, 32
	brge enough
	ldi ZH, hi(wait_cycles_ijmp+32)
	ldi ZL, lo(wait_cycles_ijmp+32)
	sbiw ZH:ZL, r24 ; substract cycles
	ijmp
wait_cycles_ijmp:
	nop
	...
	nop
	ret	; 4 cycles

enough:
	TODO exact_cycles_8



; 3rd version of 1 byte wait implementation: further reduce minimum possible wait. Implementation is a macro
; Minimum value is 7. Values less than 7 also wait 7 cycles. Plus load time: 4 cycles
; Static allocation of jump table to ZH=1 ZL=0 and static allocation of ZH to this feature would reduce load cycles to 1 or 2
#define exact_cycles_3_8(value) \
	ldi ZH, hi(wait_cycles_ijmp_addr) \
	ldi ZL, lo(wait_cycles_ijmp_addr) \
	sub ZL, r24 ; substract cycles \
	sbc ZH, ZERO ; substract cycles ; all 4 cycle to load correct jump value \
	icall ; 3 cycle+4ret = 7

wait_cycles_ijmp:
	nop
	...
	nop
wait_cycles_ijmp_ret:
	ret	
	ret
	...
	ret
wait_cycles_ijmp_addr:
	ret
	


