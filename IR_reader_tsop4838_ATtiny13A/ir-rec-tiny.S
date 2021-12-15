// CPU_FREQ: 9600000Hz
// Overflow freq: 37500Hz T=: 26micros
// Overflow 256 freq: 146Hz T=: 6849micros
// Stack frames of all IT handlers - possible to be on the stack at the same time: 14
// Turn off timeout in ovf cycles: 34615384

// Bitbang baud rate divisor and exact value: 221:5 = 3993cycles 2404Hz

#include <avr/io.h>

ZERO    = 1

/// Remaining number of bits to receive 0 means there is a valid received value in DATAs.
/// 0 also means that receiver is disabled
/// main loop has to reset this value to non 0 after processing the received value
RECEIVER_DATA_REMAINING=2
RECEIVER_DATA_0=3
RECEIVER_DATA_1=4
RECEIVER_DATA_2=5
RECEIVER_DATA_3=6

/// Simple UART output - 7 bit, no stopbit
UART_BYTE=7
UART_STATE=8
UART_DIVISOR=9

UART_RR_1=10
UART_RR_2=11
UART_RR_3=12
UART_RR_4=13
UART_RR_N=14
UART_RR_BIT=15

// Generic registers
tmp0=16
regA=tmp0 // ALias for bitbang uart

tmp1=17
loopA=tmp1  // ALias for bitbang uart
tmp2=18
loopB=tmp2  // ALias for bitbang uart
tmp3=19
loopC=tmp3 // ALias for bitbang uart

// IR receiver state
RECEIVER_STATE=20
RECEIVER_TIMEOUT=21
// 32 micros * 65535 = 2097120 micros - more than enough
RECEIVER_T1=22
RECEIVER_T0=23

// Timer overflow counter
ovf0=24
ovf1=25
ovf2=26
ovf3=27
tmp4=28

// The required PWM width - current actual width may be different until it is slowly adjusted to this value
PWM_REQ=29

// Z is r30 - this is not practical to use for specific purpose

// Only overflows are used as time base. It is about 32 micros per overflow which is more than enough precision for our purpose


#define STATE_IDLE 0
#define STATE_START_HIGH 1
#define STATE_START_LOW 2
#define STATE_DATA_HIGH 3
#define STATE_DATA_LOW 4
#define STATE_DISABLED 5
#define pcint__COUNT 6

#define UART_PORT _SFR_IO_ADDR(PORTB)
UART_TX = PB2	// not connected on the PCB
IR_INPUT = PCINT4 // IR input pin - 

// PWM output: OC0A, Pin 5 (4th on the right from top), PB0
PWM_PIN = PB0

BUTTON_PLUS_PIN = PB1 // Button input pin
BUTTON_MINUS_PIN = PB0 // Button input pin

.global	lastUserInteraction
//	.noinit
	.section .noinit
	.type	lastUserInteraction, @object
	.size	lastUserInteraction, 4
lastUserInteraction:
	.zero	4


.global	lastPWMAdjust
	.section .noinit
	.type	lastPWMAdjust, @object
	.size	lastPWMAdjust, 4
lastPWMAdjust:
	.zero	4

    .section .text
    .global main                // Note [5]
main:
   lds tmp0, OSCCAL
   inc tmp0
   inc tmp0
   inc tmp0
   sts OSCCAL, tmp0
    // SAVE REGS Stack frame size: 2 bytes
    // TODO stack frame of main method could be spared if necessary because this function never returns.
// TODO    sbi _SFR_IO_ADDR(DDRB), OUTPUT
// TODO    cbi _SFR_IO_ADDR(PORTB), OUTPUT
    
    sbi _SFR_IO_ADDR(PORTB), UART_TX // Output set to 1 - this is the idle state for TTL UART
    sbi _SFR_IO_ADDR(DDRB), UART_TX
    
    // Setup button input
    
    sbi _SFR_IO_ADDR(PORTB), BUTTON_MINUS_PIN // Pullup resistor on
    cbi _SFR_IO_ADDR(DDRB), BUTTON_MINUS_PIN // Input
    sbi _SFR_IO_ADDR(PORTB), BUTTON_PLUS_PIN // Pullup resistor on
    cbi _SFR_IO_ADDR(DDRB), BUTTON_PLUS_PIN // Input
    
    cbi _SFR_IO_ADDR(PORTB), PWM_PIN // Set initial output to low
    sbi _SFR_IO_ADDR(DDRB), PWM_PIN // Configure pin to output
    
    ldi tmp0, _BV(TOIE0)
    sts TIMSK, tmp0
    ldi tmp0, _BV(CS00)     ; tmr0:  CK/1
    out _SFR_IO_ADDR(TCCR0B), tmp0
    ldi tmp0, 0
    out _SFR_IO_ADDR(TCNT0), tmp0
    
    ldi RECEIVER_STATE, 0
    ldi ovf0, 0
    ldi ovf1, 0
    mov ZERO, ovf0

    // Enable receiver
    ldi tmp0, 1
    mov RECEIVER_DATA_REMAINING, tmp0
    
    ldi tmp0, _BV(PCIE)
    sts GIMSK, tmp0

    ldi tmp0, _BV(PCIF)
    sts GIFR, tmp0 // Clear the interrupt active flag if there was one unhandled before!
    
    ldi tmp0, _BV(IR_INPUT)
    sts PCMSK, tmp0

    // Setup output
    ldi PWM_REQ, 0
    sts OCR0A, PWM_REQ
    
    sts lastUserInteraction, ZERO // Initialize the last user interaction timestamp
    sts lastUserInteraction+1, ZERO
    sts lastUserInteraction+2, ZERO
    sts lastUserInteraction+3, ZERO
    
    sei

main_loop:
    rcall checkPWMAdjust
    brcc main_loop_UART
    lds tmp0, OCR0A
    cp tmp0, PWM_REQ
    breq main_loop_UART
    brlo main_loop_PWM_LOW
    dec tmp0
    dec tmp0
main_loop_PWM_LOW:
    inc tmp0
    rcall updatePwm

main_loop_UART:
    rcall checkTimeoutTurnOff
    
main_BUTTON_INPUT:
    rcall isUserInteractionAllowed
    brcc main_INPUT_BLOCKED
    
    in tmp0, _SFR_IO_ADDR(PINB)
    sbrs tmp0, BUTTON_MINUS_PIN // Low when button is pressed
    rcall inputButtonMinus
    in tmp0, _SFR_IO_ADDR(PINB)
    sbrs tmp0, BUTTON_PLUS_PIN // Low when button is pressed
    rcall inputButtonPlus

    // rjmp main_IR_RECEIVE
main_INPUT_BLOCKED:
    // ldi tmp0, 'B'  // LOG
    // rcall uartSendBlock
    
main_IR_RECEIVE:
    TST RECEIVER_DATA_REMAINING // IR remote controller input
    brne main_loop

    // Data received
    mov tmp0, RECEIVER_DATA_3 // Log to user
    rcall txchar
    mov tmp0, RECEIVER_DATA_2
    rcall txchar
    mov tmp0, RECEIVER_DATA_1
    rcall txchar
    mov tmp0, RECEIVER_DATA_0
    rcall txchar

/*    rcall getSinceLastUserInteraction
    
    ldi ZL, lo8(irRepeatTimeout)
    ldi ZH, hi8(irRepeatTimeout)
    rcall comparePointerToTime
    brlo main_IR_RECEIVE_end
*/

    rcall isUserInteractionAllowed
    brcc main_IR_RECEIVE_end


    ldi	ZL, lo8(pattern_power)
    ldi	ZH, hi8(pattern_power)
    rcall testPattern
    brne main_NOT_POWER
    rcall inputIRPower
main_NOT_POWER:

    ldi	ZL, lo8(pattern_plus)
    ldi	ZH, hi8(pattern_plus)
    rcall testPattern
    brne main_NOT_PLUS
    rcall inputIRPlus
main_NOT_PLUS:


    ldi	ZL, lo8(pattern_minus)
    ldi	ZH, hi8(pattern_minus)
    rcall testPattern
    brne main_NOT_MINUS
    rcall inputIRMinus
main_NOT_MINUS:

main_IR_RECEIVE_end:
    ldi tmp0, 1 // Reenable data input
    mov RECEIVER_DATA_REMAINING, tmp0
    rjmp main_loop
    // RESTORE SAVED REGS ([])
//    ret // This is a formal ret but never reached normally
//    ret // This is a formal ret but never reached normally

// Check if pattern is received. Return is in SREG BRNE can be used to test
testPattern:
    lpm tmp1, Z+
    cp RECEIVER_DATA_3, tmp1
    lpm tmp1, Z+
    cpc RECEIVER_DATA_2, tmp1
    lpm tmp1, Z+
    cpc RECEIVER_DATA_1, tmp1
    lpm tmp1, Z+
    cpc RECEIVER_DATA_0, tmp1
    ret


pattern_minus:
    .byte 0B11100000
    .byte 0B11100000
    .byte 0B11010000
    .byte 0B00101111
    
pattern_plus:
    .byte 0B11100000
    .byte 0B11100000
    .byte 0B11100000
    .byte 0B00011111

pattern_power:
    .byte 0B11100000
    .byte 0B11100000
    .byte 0B01000000
    .byte 0B10111111



/// Update PWM output to value in tmp0
updatePwm:
    tst tmp0
    // Always store the current value into this register even when PWM is disabled
    sts OCR0A, tmp0
    breq updatePwm_zero
    // Fast PWM mode WGM0[2:0]=0x3
    // COM0A1:COM0A0 10 (non inverting mode)
//    ldi tmp0, _BV(COM0A1)|_BV(WGM01)|_BV(WGM00)     // COM0A: 10 - non inverting mode WGM0[0:1]: 11 Fast PWM
//    out _SFR_IO_ADDR(TCCR0A), tmp0
    rjmp updatePwm_ret
updatePwm_zero:
    // Normal mode WGM0[2:0]=0x0
    // COM0A1:COM0A0 00 (OC0A disconnected)
    ldi tmp0, 0     // Disable PWM output
//    out _SFR_IO_ADDR(TCCR0A), tmp0
//    cbi _SFR_IO_ADDR(PORTB), PWM_PIN // Set initial output to low
updatePwm_ret:
    ret


inputButtonMinus:
    ldi tmp0, 0x0f
    rcall txchar
    rcall saveLastUserInteraction
    cpi PWM_REQ, 31 // Step 1 to 0
    brne inputButtonMinus_NOT_1
    ldi PWM_REQ, 0
inputButtonMinus_NOT_1:
    cpi PWM_REQ, 63 // Step 2 to 1
    brne inputButtonMinus_NOT_2
    ldi PWM_REQ, 31
inputButtonMinus_NOT_2:
    cpi PWM_REQ, 95 // Step 3 to 2
    brne inputButtonMinus_NOT_3
    ldi PWM_REQ, 63
inputButtonMinus_NOT_3:
    cpi PWM_REQ, 127 // Step 4 to 3
    brne inputButtonMinus_NOT_4
    ldi PWM_REQ, 95
inputButtonMinus_NOT_4:
    cpi PWM_REQ, 159 // Step 5 to 4
    brne inputButtonMinus_NOT_5
    ldi PWM_REQ, 127
inputButtonMinus_NOT_5:
    cpi PWM_REQ, 192 // Step 6 to 5
    brne inputButtonMinus_NOT_6
    ldi PWM_REQ, 159
inputButtonMinus_NOT_6:
    cpi PWM_REQ, 225 // Step 7 to 6
    brne inputButtonMinus_NOT_7
    ldi PWM_REQ, 192
inputButtonMinus_NOT_7:
    cpi PWM_REQ, 255 // Step 8 to 7
    brne inputButtonMinus_NOT_8
    ldi PWM_REQ, 225
inputButtonMinus_NOT_8:
    ret

inputButtonPlus:
    ldi tmp0, '+'
    rcall txchar
    rcall saveLastUserInteraction
    cpi PWM_REQ, 225 // Step 7 to 8
    brne inputButtonPlus_NOT_7
    ldi PWM_REQ, 255
inputButtonPlus_NOT_7:
    cpi PWM_REQ, 192 // Step 6 to 7
    brne inputButtonPlus_NOT_6
    ldi PWM_REQ, 225
inputButtonPlus_NOT_6:
    cpi PWM_REQ, 159 // Step 5 to 6
    brne inputButtonPlus_NOT_5
    ldi PWM_REQ, 192
inputButtonPlus_NOT_5:
    cpi PWM_REQ, 127 // Step 4 to 5
    brne inputButtonPlus_NOT_4
    ldi PWM_REQ, 159
inputButtonPlus_NOT_4:
    cpi PWM_REQ, 95 // Step 3 to 4
    brne inputButtonPlus_NOT_3
    ldi PWM_REQ, 127
inputButtonPlus_NOT_3:
    cpi PWM_REQ, 63 // Step 2 to 3
    brne inputButtonPlus_NOT_2
    ldi PWM_REQ, 95
inputButtonPlus_NOT_2:
    cpi PWM_REQ, 31 // Step 1 to 2
    brne inputButtonPlus_NOT_1
    ldi PWM_REQ, 63
inputButtonPlus_NOT_1:
    cpi PWM_REQ, 0 // Step 0 to 1
    brne inputButtonPlus_NOT_0
    ldi PWM_REQ, 31
inputButtonPlus_NOT_0:
    ret

inputIRMinus:
    rcall inputButtonMinus
    tst PWM_REQ
    brne inputIRMinus_ret
    ldi PWM_REQ, 31
inputIRMinus_ret:
    ret

inputIRPlus:
    rcall inputButtonPlus
    ret

inputIRPower:
	rcall getSinceLastUserInteraction
    
    ldi ZL, lo8(pwrRepeatTimeout)
    ldi ZH, hi8(pwrRepeatTimeout)
    rcall comparePointerToTime
    brlo inputIRPower_ret
    ldi tmp0, '/'
    rcall txchar
    rcall saveLastUserInteraction
    tst PWM_REQ
    breq inputIRPower_on
    ldi PWM_REQ, 0
    rjmp inputIRPower_ret
inputIRPower_on:
    ldi PWM_REQ, 255
inputIRPower_ret:
    ret

/// Save current time as last user interaction timestamp
/// Ruins the same registers as getTime
    .global saveLastUserInteraction
saveLastUserInteraction:
	ldi ZL, lo8(lastUserInteraction)
	ldi ZH, hi8(lastUserInteraction)
	rcall saveTimeToPointer
    ret

saveTimeToPointer:
    rcall getTime
    st Z+, tmp0
    st Z+, tmp1
    st Z+, tmp2
    st Z+, tmp3
	


/// checkPWMAdjust
/// Ruins registers
/// returns carry flag set if PWM adjust time has come
    .global checkPWMAdjust
checkPWMAdjust:
    ldi	ZL, lo8(lastPWMAdjust)
    ldi	ZH, hi8(lastPWMAdjust)
    rcall getTimeSincePointer
    ldi	ZL, lo8(pwmAdjustTimeout)
    ldi	ZH, hi8(pwmAdjustTimeout)
    rcall comparePointerToTime
    
    brlo checkPWMAdjust_ret_false
    
    ldi ZL, lo8(lastPWMAdjust)
    ldi ZH, hi8(lastPWMAdjust)
    rcall saveTimeToPointer
    sec
    rjmp checkPWMAdjust_ret
checkPWMAdjust_ret_false:
    clc
checkPWMAdjust_ret:
    ret
    
pwmAdjustTimeout:
.byte 0x80
.byte 0x1
.byte 0x0
.byte 0x0

/// Get time and substract the value at SRAM pointer from it
/// Ret is in tmp3:tmp0
getTimeSincePointer:
    rcall getTime
    
    ld tmp4, Z+
    sub tmp0, tmp4
    ld tmp4, Z+
    sbc tmp1, tmp4
    ld tmp4, Z+
    sbc tmp2, tmp4
    ld tmp4, Z+
    sbc tmp3, tmp4

// Compare value in Program memory to time in tmp3:tmp0
comparePointerToTime:
    lpm tmp4, Z+ // Compare to timeout
    cp tmp0, tmp4
    lpm tmp4, Z+
    cpc tmp1, tmp4
    lpm tmp4, Z+
    cpc tmp2, tmp4
    lpm tmp4, Z+
    cpc tmp3, tmp4
    ret

    
/// Check whether turn off timeout is reached?
/// If true then turns the lamp off and saves current time as last user interaction (just to avoid overflow)
/// Does not preserve temporary registers
    .global checkTimeoutTurnOff
checkTimeoutTurnOff:
    rcall getSinceLastUserInteraction
    ldi ZL, lo8(turnOffTimeout)
    ldi ZH, hi8(turnOffTimeout)
    rcall comparePointerToTime
    brlo checkTimeoutTurnOff_ret
    ldi PWM_REQ, 0
    rcall saveLastUserInteraction
checkTimeoutTurnOff_ret:
    ret

turnOffTimeout:
.byte 0x58
.byte 0x30
.byte 0x10
.byte 0x2

/// Is user interaction allowed by timeout?
/// Interaction is disabled for a period of time
/// Does button debouncing, button auto-repeat and IR autorepeat as well
/// Return carry is set if user interaction is allowed
/// Changed: SREG, "tmp0", "tmp1","tmp2", "tmp3", "tmp4"
    .global isUserInteractionAllowed
isUserInteractionAllowed:
    // SAVE REGS Stack frame size: 2 bytes
    rcall getSinceLastUserInteraction
    
    ldi ZL, lo8(repeatTimeout)
    ldi ZH, hi8(repeatTimeout)
    rcall comparePointerToTime
    brlo isUserInteractionAllowed_no
    sec
    rjmp isUserInteractionAllowed_ret
isUserInteractionAllowed_no:
    clc
isUserInteractionAllowed_ret:
    // RESTORE SAVED REGS ([])
    ret

repeatTimeout:
.byte 0x83
.byte 0x7
.byte 0x0
.byte 0x0

pwrRepeatTimeout: // Power button has stricter repeat timeout because it is very easy to double click
.byte 0xa1
.byte 0x52
.byte 0x0
.byte 0x0

/// Get time spent since last user interaction (in overflow ticks)
/// Ruins the same registers as getTime
/// Returned value is in tmp3:tmp2:tmp1:tmp0
    .global getSinceLastUserInteraction
getSinceLastUserInteraction:
    // SAVE REGS Stack frame size: 3 bytes
    push tmp4
	ldi ZL, lo8(lastUserInteraction)
	ldi ZH, hi8(lastUserInteraction)
	rcall getTimeSincePointer
    // RESTORE SAVED REGS ([tmp4])
    pop tmp4
    ret

/// Read current time from timer0 overflow counter. TCNT0 is not read only the overflows
/// 32 bits returned in: tmp3:tmp2:tmp1:tmp0
/// status byte is ruined
/// others are not touched
    .global getTime
getTime:
    cli
    mov tmp0, ovf0
    mov tmp1, ovf1
    mov tmp2, ovf2
    mov tmp3, ovf3
    sei
    ret


    .global TIM0_OVF_vect         // Note [7]
TIM0_OVF_vect:
    // SAVE REGS in interrupt. Stack frame size: 5 bytes
    push r0
    in r0,_SFR_IO_ADDR(SREG)
    push tmp0
    push r0
    
// PWM output
    lds tmp0, OCR0A
    tst tmp0
    breq lamp_off
    cp tmp0, ovf0
    brge lamp_off
    sbi _SFR_IO_ADDR(PORTB), PWM_PIN
    rjmp goon
lamp_off:
    cbi _SFR_IO_ADDR(PORTB), PWM_PIN
goon:
// Increment ovfX 4 bytes and also save the previous value of ovf1
    mov r0, ovf1
    ldi tmp0, 1
    add    ovf0, tmp0
    ldi tmp0, 0
    adc    ovf1, tmp0
    adc    ovf2, tmp0
    adc    ovf3, tmp0
    
    // If ovf1 have changed - Every 256th overflow decreases this timeout counter
    cp r0, ovf1
    breq timer_ret
    // 256 overflow cycles!
    TST RECEIVER_TIMEOUT
    BREQ timer_ret
    dec RECEIVER_TIMEOUT
    TST RECEIVER_TIMEOUT
    BRNE timer_ret
    ldi RECEIVER_STATE, STATE_IDLE // In case of timeout the receiver goes to idle state

timer_ret:
    // RESTORE SAVED REGS ([tmp0, r0])
    pop r0
    pop tmp0
    out _SFR_IO_ADDR(SREG), r0
    pop r0
    reti

// Save the current time at state change
// Reads time using getTime
// Save time to ...
// Resets the RECEIVER_TIMEOUT to 3
// Changes: tmp0, tmp1, tmp2, tmp3, SREG
saveCurrentTime:
    // SAVE REGS Stack frame size: 2 bytes
   rcall getTime
   cpi RECEIVER_TIMEOUT, 3
   brge saveCurrentTime_noreset
   ldi RECEIVER_TIMEOUT, 3
saveCurrentTime_noreset:
   mov RECEIVER_T0, tmp0
   mov RECEIVER_T1, tmp1
    // RESTORE SAVED REGS ([])
   ret

/// Disable receiver until a timeout. Must be called after data was received or after
.global disableReceiverTimeout
disableReceiverTimeout:
   ldi RECEIVER_TIMEOUT, 36 // timeout to go to STATE_IDLE ~250 millis
   ldi RECEIVER_STATE, STATE_DISABLED
   ret


/// Received bit is in tmp0 (0 or 1)
/// shift received 4 bytes, write value.
/// Update data counter. in case of last bit received disable further input and call received handler
.global dataReceived
dataReceived:
    ror tmp0 // Put bit into carry
    rol RECEIVER_DATA_0 // Shift bit into storage
    rol RECEIVER_DATA_1
    rol RECEIVER_DATA_2
    rol RECEIVER_DATA_3
    dec RECEIVER_DATA_REMAINING
    tst RECEIVER_DATA_REMAINING
    BRNE dataReceived_ret

    // Main program knows that data was received by RECEIVER_DATA_REMAINING==0 
    rcall disableReceiverTimeout
    
    // if 0 -> rcall disableReceiverTimeout // Data received next data must wait timeout
    // Also signal input ready so it can be processed!
dataReceived_ret:
    ret


// Pin change on input
.global PCINT0_vect
PCINT0_vect:
    // SAVE REGS in interrupt. Stack frame size: 9 bytes
    push r0
    in r0,_SFR_IO_ADDR(SREG)
    push tmp0
    push tmp1
    push tmp2
    push tmp3
    push ZL
    push ZH
// Disable PIN change interrupt
    ldi tmp0, 0
    sts GIMSK, tmp0
    ldi tmp0, _BV(PCIF)
    sts GIFR, tmp0 // Clear the interrupt active flag if there was one during the first instructions of this handler!

    ldi RECEIVER_TIMEOUT, 3 // If not yet then do not timeout here!

    sei // Pin change interrupt is disabled so this can not be re-called.
    // Timer overflow counting must not be blocked longer than about 128 cycles!

    tst RECEIVER_DATA_REMAINING
    BRNE pcint_enabled
    rjmp pcint_ret // RECEIVER_DATA_REMAINING 0 disables the receiver totally
pcint_enabled:

    RCALL getTime

    // Count time spent since last pin change tmp1:tmp0 stores the result
    sub tmp0,RECEIVER_T0
    sbc tmp1,RECEIVER_T1

    mov tmp2, RECEIVER_STATE   // Addresses are auto-multipled by 2 in case of ROM address
    ldi	ZL, lo8(pm(pcint__sw_table))
    ldi	ZH, hi8(pm(pcint__sw_table))
    ldi tmp3, 0

    cpi tmp2, pcint__COUNT
    BRLT pcint__jump
    ldi tmp2, 0 // In case of invalid state reset to state 0
pcint__jump:
    add ZL, tmp2
    adc ZH, tmp3
    ijmp
pcint__sw_table:
    rjmp pcint__STATE_IDLE
    rjmp pcint__STATE_START_HIGH
    rjmp pcint__STATE_START_LOW
    rjmp pcint__STATE_DATA_HIGH
    rjmp pcint__STATE_DATA_LOW
    rjmp pcint__STATE_DISABLED


pcint__STATE_IDLE:
    ldi RECEIVER_STATE, STATE_START_HIGH // Independent of T we assume this is a start edge
    rjmp pcint__end

pcint__STATE_START_HIGH:
    ldi tmp2, 0x4c
    cp tmp0, tmp2
    ldi tmp2, 0x0
    cpc tmp1, tmp2
    brge pcint__STATE_START_HIGH_RangeGt_2000 // If measured value is GT 2000 micros (76 ticks)
pcint__STATE_START_HIGH_Range_0_TO_2000:
    rcall disableReceiverTimeout // Start HIGH is too short
    rjmp pcint__STATE_START_HIGH_Range_EXIT
pcint__STATE_START_HIGH_RangeGt_2000:
    ldi tmp2, 0xa7
    cp tmp0, tmp2
    ldi tmp2, 0x1
    cpc tmp1, tmp2
    brge pcint__STATE_START_HIGH_RangeGt_11000 // If measured value is GT 11000 micros (423 ticks)
pcint__STATE_START_HIGH_Range_2000_TO_11000:
    ldi RECEIVER_STATE, STATE_START_LOW // Correct Start_HIGH signal moves us into START_LOW state
    rjmp pcint__STATE_START_HIGH_Range_EXIT
pcint__STATE_START_HIGH_RangeGt_11000:
    rcall disableReceiverTimeout // Start HIGH is too long
pcint__STATE_START_HIGH_Range_EXIT:

    rjmp pcint__end

pcint__STATE_START_LOW:
    ldi tmp2, 0xb
    cp tmp0, tmp2
    ldi tmp2, 0x0
    cpc tmp1, tmp2
    brge pcint__STATE_START_LOW_RangeGt_300 // If measured value is GT 300 micros (11 ticks)
pcint__STATE_START_LOW_Range_0_TO_300:
    rcall disableReceiverTimeout // Signal too short
    rjmp pcint__STATE_START_LOW_Range_EXIT
pcint__STATE_START_LOW_RangeGt_300:
    ldi tmp2, 0xa7
    cp tmp0, tmp2
    ldi tmp2, 0x1
    cpc tmp1, tmp2
    brge pcint__STATE_START_LOW_RangeGt_11000 // If measured value is GT 11000 micros (423 ticks)
pcint__STATE_START_LOW_Range_300_TO_11000:
    ldi tmp0, 32 // Set awaited number of bits
    mov RECEIVER_DATA_REMAINING, tmp0
    ldi tmp0, 0 // Clear data receiver registers
    mov RECEIVER_DATA_0, tmp0
    mov RECEIVER_DATA_1, tmp0
    mov RECEIVER_DATA_2, tmp0
    mov RECEIVER_DATA_3, tmp0
    ldi RECEIVER_STATE, STATE_DATA_HIGH // Await first bit
    rjmp pcint__STATE_START_LOW_Range_EXIT
pcint__STATE_START_LOW_RangeGt_11000:
    rcall disableReceiverTimeout // Signal too long
pcint__STATE_START_LOW_Range_EXIT:

    rjmp pcint__end

pcint__STATE_DATA_HIGH:
    ldi tmp2, 0xb
    cp tmp0, tmp2
    ldi tmp2, 0x0
    cpc tmp1, tmp2
    brge pcint__STATE_DATA_HIGH_RangeGt_300 // If measured value is GT 300 micros (11 ticks)
pcint__STATE_DATA_HIGH_Range_0_TO_300:
    rcall disableReceiverTimeout // Invalid signal length
    rjmp pcint__STATE_DATA_HIGH_Range_EXIT
pcint__STATE_DATA_HIGH_RangeGt_300:
    ldi tmp2, 0x26
    cp tmp0, tmp2
    ldi tmp2, 0x0
    cpc tmp1, tmp2
    brge pcint__STATE_DATA_HIGH_RangeGt_1000 // If measured value is GT 1000 micros (38 ticks)
pcint__STATE_DATA_HIGH_Range_300_TO_1000:
    // Valid length of data HIGH - go to LOW sate
    ldi RECEIVER_STATE, STATE_DATA_LOW
    rjmp pcint__STATE_DATA_HIGH_Range_EXIT
pcint__STATE_DATA_HIGH_RangeGt_1000:
    rcall disableReceiverTimeout // Invalid signal length
pcint__STATE_DATA_HIGH_Range_EXIT:
    rjmp pcint__end

pcint__STATE_DATA_LOW:
    ldi tmp2, 0xb
    cp tmp0, tmp2
    ldi tmp2, 0x0
    cpc tmp1, tmp2
    brge pcint__STATE_DATA_LOW_RangeGt_300 // If measured value is GT 300 micros (11 ticks)
pcint__STATE_DATA_LOW_Range_0_TO_300:
    rcall disableReceiverTimeout // Invalid signal length
    rjmp pcint__STATE_DATA_LOW_Range_EXIT
pcint__STATE_DATA_LOW_RangeGt_300:
    ldi tmp2, 0x26
    cp tmp0, tmp2
    ldi tmp2, 0x0
    cpc tmp1, tmp2
    brge pcint__STATE_DATA_LOW_RangeGt_1000 // If measured value is GT 1000 micros (38 ticks)
pcint__STATE_DATA_LOW_Range_300_TO_1000:
    ldi RECEIVER_STATE, STATE_DATA_HIGH
    ldi tmp0, 0 // Received bit
    rcall dataReceived
    rjmp pcint__STATE_DATA_LOW_Range_EXIT
pcint__STATE_DATA_LOW_RangeGt_1000:
    ldi tmp2, 0x4c
    cp tmp0, tmp2
    ldi tmp2, 0x0
    cpc tmp1, tmp2
    brge pcint__STATE_DATA_LOW_RangeGt_2000 // If measured value is GT 2000 micros (76 ticks)
pcint__STATE_DATA_LOW_Range_1000_TO_2000:
    ldi RECEIVER_STATE, STATE_DATA_HIGH
    ldi tmp0, 1  // Received bit
    rcall dataReceived
    rjmp pcint__STATE_DATA_LOW_Range_EXIT
pcint__STATE_DATA_LOW_RangeGt_2000:
    rcall disableReceiverTimeout // Invalid signal length
pcint__STATE_DATA_LOW_Range_EXIT:
    rjmp pcint__end

pcint__STATE_DISABLED:
    // In disabled state we do not process any input. Disabled state will be left by timer timeout which moves us to the idle state
pcint__end:
    // Save the last processed pin change time and clear timeout
    rcall saveCurrentTime
pcint_ret:
    ldi tmp0, _BV(PCIE)
    sts GIMSK, tmp0

    ldi tmp0, _BV(PCIF)
    sts GIFR, tmp0 // Clear the interrupt active flag if there was one unhandled before!
    
    ldi tmp0, _BV(IR_INPUT)
    sts PCMSK, tmp0
    // RESTORE SAVED REGS ([tmp0, tmp1, tmp2, tmp3, ZL, ZH])
    pop ZH
    pop ZL
    pop tmp3
    pop tmp2
    pop tmp1
    pop tmp0
    out _SFR_IO_ADDR(SREG), r0
    pop r0
    reti

// Send byte in tmp0 (alias regA) with bitbang uart. Blocking call waits until send is ready
txchar:				;transmit character in regA out the port bit
    cli
	cbi	UART_PORT,UART_TX		;begin start bit
	rcall	txrxbd		;bit time delay				// C3 + txrxbd
	ldi	loopC,8		;8 data bits, no parity			// C1
txc1:	ror	regA		;rotate bit 0 into carry	// C1
	brcs	txc2		;branch if bit is high      // C1/ C2(if jump)
	cbi	UART_PORT,UART_TX							// C1
	rjmp	txc3									// C2
txc2:	sbi	UART_PORT,UART_TX								// C1
txc3:	rcall	txrxbd		;bit time delay			// C3 + txrxbd
	dec	loopC										// C1
	brne	txc1		;loop until all bits done	// C1/C2(if jump)
	sbi	UART_PORT,UART_TX		;begin the stop bit
	rcall	txrxbd		;bit time delay
				;wait another bit time before next character
				;(sends 2 stop bits)
	rcall	txrxbd		;bit time delay
	sei
	ret

;--------------------
				;bit delay, common to tx and rx routines
txrxbd:	ldi loopA,221	;coarse bit timing value // C1
txrx5:	ldi	loopB,5	;fine bit timing value   // C1
txrx4:	dec	loopB		;inner loop // C1
	brne	txrx4					// C2 (it jump)/ C1 if exit
// Clocks: ((loopB*3)+4-1)*loopA +1+4  (Outer loop is 4 cycles but last inner loop is shorter by one cycle and we correct that in the equatation)
	dec	loopA		;outer loop // C1
	brne	txrx5               // C2 (if jump)
	ret
    .global __vector_default        // Note [10]
__vector_default:
    reti
    .end

