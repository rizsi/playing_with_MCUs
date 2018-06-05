package genirrec;

abstract public class IrRecS extends AsmWithRangeCheckAbstract {
	public static void main(String[] args) {
		new IrRecSAtmega().generate();
	}
	private String currentReceivedLabel;
	protected boolean uart=true;
	protected int uartBaud=2400;
	protected int bdHigh=1;
	protected int bdLow=1;
	protected int loopBMul=3;
	protected int loopAMul=4-1; // Outer loop is 4 cycles and 1 is correction of last shorter inner loop
	protected boolean debugLED=true;
	
	private int[] step={0, 31, 63, 95, 127, 159, 192, 225, 255};
//	private int[] step={0, 255};

	public IrRecS() {
		setup();
		int nCycle=cpu_freq/uartBaud;
		bdLow=0;
		bdHigh=256;
		// System.out.println("nCycle: "+nCycle);
		while(bdHigh>255)
		{
			bdLow++;
			bdHigh=(nCycle-15)/((bdLow*loopBMul)+loopAMul);
		}
		if(bdHigh>255)
		{
			throw new RuntimeException("Problem with bitbang timings - bdHight more than 255 "+bdHigh +"(Increase bdLow or increase baud rate)");
		}
		if(bdLow>255)
		{
			throw new RuntimeException("Problem with bitbang timings - bdLow more than 255 "+bdLow +"(increase baud rate)");
		}
	}
	abstract protected void setup();
	protected void generate() {
		int ovfHz=cpu_freq/256;
		int ovfTMicros=(int)(1.0/ovfHz*1000000);
		int ovf256Hz=cpu_freq/256/256;
		int ovf256TMicros=(int)(1.0/ovf256Hz*1000000);
		int uart_divisor=cpu_freq/256/uartBaud;
		int repeatTimeout=50000/ovfTMicros; // 50 millis
		int pwrRepeatTimeout=550000/ovfTMicros; // 550 millis
		int turnOffTimeout=(15*60)*1000000/ovfTMicros; // 15 minutes
		int pwmAdjustTimeout=10*1000/ovfTMicros; // 3 millis
		int bitbangCycles=((bdLow*loopBMul)+loopAMul)*bdHigh +1+4+10;
		int bitbangHz=cpu_freq/bitbangCycles;
		write("// CPU_FREQ: ");
		writeObject(cpu_freq);
		write("Hz\n// Overflow freq: ");
		writeObject(ovfHz);
		write("Hz T=: ");
		writeObject(ovfTMicros);
		write("micros\n// Overflow 256 freq: ");
		writeObject(ovf256Hz);
		write("Hz T=: ");
		writeObject(ovf256TMicros);
		write("micros\n// Stack frames of all IT handlers - possible to be on the stack at the same time: ");
		deferred(this::printAllStackSize);
		write("\n// Turn off timeout in ovf cycles: ");
		writeObject(turnOffTimeout);
		write("\n\n// Bitbang baud rate divisor and exact value: ");
		writeObject(bdHigh);
		write(":");
		writeObject(bdLow);
		write(" = ");
		writeObject(bitbangCycles);
		write("cycles ");
		writeObject(bitbangHz);
		write("Hz\n\n#include <avr/io.h>\n\nZERO    = 1\n\n/// Remaining number of bits to receive 0 means there is a valid received value in DATAs.\n/// 0 also means that receiver is disabled\n/// main loop has to reset this value to non 0 after processing the received value\nRECEIVER_DATA_REMAINING=2\nRECEIVER_DATA_0=3\nRECEIVER_DATA_1=4\nRECEIVER_DATA_2=5\nRECEIVER_DATA_3=6\n\n/// Simple UART output - 7 bit, no stopbit\nUART_BYTE=7\nUART_STATE=8\nUART_DIVISOR=9\n\nUART_RR_1=10\nUART_RR_2=11\nUART_RR_3=12\nUART_RR_4=13\nUART_RR_N=14\nUART_RR_BIT=15\n\n// Generic registers\ntmp0=16\nregA=tmp0 // ALias for bitbang uart\n\ntmp1=17\nloopA=tmp1  // ALias for bitbang uart\ntmp2=18\nloopB=tmp2  // ALias for bitbang uart\ntmp3=19\nloopC=tmp3 // ALias for bitbang uart\n\n// IR receiver state\nRECEIVER_STATE=20\nRECEIVER_TIMEOUT=21\n// 32 micros * 65535 = 2097120 micros - more than enough\nRECEIVER_T1=22\nRECEIVER_T0=23\n\n// Timer overflow counter\novf0=24\novf1=25\novf2=26\novf3=27\ntmp4=28\n\n// The required PWM frequency - current actual frequency may be different until it is slowly adjusted to this value\nPWM_REQ=29\n\n// Z is r30 - this is not practical to use for specific purpose\n\n// Only overflows are used as time base. It is about 32 micros per overflow which is more than enough precision for our purpose\n\n\n");
		generateSwitchStates();
		write("\n");
		generatePinout();
		write("\n.global\tlastUserInteraction\n//\t.noinit\n\t.section .noinit\n\t.type\tlastUserInteraction, @object\n\t.size\tlastUserInteraction, 4\nlastUserInteraction:\n\t.zero\t4\n\n\n.global\tlastPWMAdjust\n\t.section .noinit\n\t.type\tlastPWMAdjust, @object\n\t.size\tlastPWMAdjust, 4\nlastPWMAdjust:\n\t.zero\t4\n\n    .section .text\n    .global main                // Note [5]\nmain:\n   lds tmp0, OSCCAL\n   inc tmp0\n   inc tmp0\n   inc tmp0\n   sts OSCCAL, tmp0\n");
		saveRegs();
		write("    // TODO stack frame of main method could be spared if necessary because this function never returns.\n");
		generateInitPins();
		write("    \n");
		generateSetupTimer();
		write("    ldi RECEIVER_STATE, 0\n    ldi ovf0, 0\n    ldi ovf1, 0\n    mov ZERO, ovf0\n\n");
		if(uart)
		{
			write("    mov UART_STATE, ZERO\n    mov UART_RR_1, ZERO\n    mov UART_RR_2, ZERO\n    mov UART_RR_3, ZERO\n    mov UART_RR_4, ZERO\n    mov UART_RR_N, ZERO\n\n    ldi tmp0, 9 // Next byte\n    mov UART_RR_BIT, tmp0\n    \n");
		}
		write("    // Enable receiver\n    ldi tmp0, 1\n    mov RECEIVER_DATA_REMAINING, tmp0\n    \n");
		enablePCINT();
		write("\n    // Setup output\n    ldi PWM_REQ, 0\n");
		setPWMRegister("PWM_REQ");
		write("    \n    sts lastUserInteraction, ZERO // Initialize the last user interaction timestamp\n    sts lastUserInteraction+1, ZERO\n    sts lastUserInteraction+2, ZERO\n    sts lastUserInteraction+3, ZERO\n    \n    sei\n\nmain_loop:\n    rcall checkPWMAdjust\n    brcc main_loop_UART\n");
		getPWMRegister("tmp0");
		write("    cp tmp0, PWM_REQ\n    breq main_loop_UART\n    brlo main_loop_PWM_LOW\n    dec tmp0\n    dec tmp0\nmain_loop_PWM_LOW:\n    inc tmp0\n    rcall updatePwm\n\nmain_loop_UART:\n");
		if(uart)
		{
			write("    rcall uartSendRR // Send bytes from UART buffer\n");
		}
		write("    rcall checkTimeoutTurnOff\n");
		if(debugLED)
		{
			write("    rcall getTime // Whats the time? Why you ask? I don't know.\n");
			clearDebugLed();
			write("    cpi tmp1,127\n    brlo main_BUTTON_INPUT\n");
			setDebugLed();
		}
		write("    \nmain_BUTTON_INPUT:\n    rcall isUserInteractionAllowed\n    brcc main_INPUT_BLOCKED\n    \n");
		readPinButtonMinus("tmp0");
		write("    sbrs tmp0, BUTTON_MINUS_PIN // Low when button is pressed\n    rcall inputButtonMinus\n");
		readPinButtonPlus("tmp0");
		write("    sbrs tmp0, BUTTON_PLUS_PIN // Low when button is pressed\n    rcall inputButtonPlus\n\n    // rjmp main_IR_RECEIVE\nmain_INPUT_BLOCKED:\n    // ldi tmp0, 'B'  // LOG\n    // rcall uartSendBlock\n    \nmain_IR_RECEIVE:\n    TST RECEIVER_DATA_REMAINING // IR remote controller input\n    brne main_loop\n\n    // Data received\n");
		if(uart){
			write("    \n    mov tmp0, RECEIVER_DATA_3 // Log to user\n    rcall uartAppendBlock\n    mov tmp0, RECEIVER_DATA_2\n    rcall uartAppendBlock\n    mov tmp0, RECEIVER_DATA_1\n    rcall uartAppendBlock\n    mov tmp0, RECEIVER_DATA_0\n    rcall uartAppendBlock\n");
		}
		else
		{
			write("    mov tmp0, RECEIVER_DATA_3 // Log to user\n    rcall txchar\n    mov tmp0, RECEIVER_DATA_2\n    rcall txchar\n    mov tmp0, RECEIVER_DATA_1\n    rcall txchar\n    mov tmp0, RECEIVER_DATA_0\n    rcall txchar\n");
		}
		write("\n/*    rcall getSinceLastUserInteraction\n    \n    ldi ZL, lo8(irRepeatTimeout)\n    ldi ZH, hi8(irRepeatTimeout)\n    rcall comparePointerToTime\n    brlo main_IR_RECEIVE_end\n*/\n\n    rcall isUserInteractionAllowed\n    brcc main_IR_RECEIVE_end\n\n\n");
		checkReceiver("main_NOT_POWER", "pattern_power");
		if(uart)
		{
			write("    ldi tmp0, '/'\n    rcall uartSendBlock\n");
		}
		write("    rcall inputIRPower\n");
		checkReceiverEnd();
		write("\n");
		checkReceiver("main_NOT_PLUS", "pattern_plus");
		if(uart)
		{
			write("    ldi tmp0, '+'\n    rcall uartSendBlock\n");
		}
		write("    rcall inputIRPlus\n");
		checkReceiverEnd();
		write("\n\n");
		checkReceiver("main_NOT_MINUS", "pattern_minus");
		if(uart)
		{
			write("    ldi tmp0, '-'\n    rcall uartSendBlock\n");
		}
		write("    rcall inputIRMinus\n");
		checkReceiverEnd();
		write("\n");
		if(uart)
		{
			write("    ldi tmp0, 'R'\n    rcall uartSendBlock\n");
		}
		write("main_IR_RECEIVE_end:\n    ldi tmp0, 1 // Reenable data input\n    mov RECEIVER_DATA_REMAINING, tmp0\n    rjmp main_loop\n");
		restoreRegs();
		write("//    ret // This is a formal ret but never reached normally\n//    ret // This is a formal ret but never reached normally\n\n// Check if pattern is received. Return is in SREG BRNE can be used to test\ntestPattern:\n    lpm tmp1, Z+\n    cp RECEIVER_DATA_3, tmp1\n    lpm tmp1, Z+\n    cpc RECEIVER_DATA_2, tmp1\n    lpm tmp1, Z+\n    cpc RECEIVER_DATA_1, tmp1\n    lpm tmp1, Z+\n    cpc RECEIVER_DATA_0, tmp1\n    ret\n\n\npattern_minus:\n    .byte 0B11100000\n    .byte 0B11100000\n    .byte 0B11010000\n    .byte 0B00101111\n    \npattern_plus:\n    .byte 0B11100000\n    .byte 0B11100000\n    .byte 0B11100000\n    .byte 0B00011111\n\npattern_power:\n    .byte 0B11100000\n    .byte 0B11100000\n    .byte 0B01000000\n    .byte 0B10111111\n\n\n\n/// Update PWM output to value in tmp0\nupdatePwm:\n    tst tmp0\n    // Always store the current value into this register even when PWM is disabled\n");
		setPWMRegister("tmp0");
		write("    breq updatePwm_zero\n");
		setupPWMNonZero();
		write("    rjmp updatePwm_ret\nupdatePwm_zero:\n");
		setupPWMZero();
		write("updatePwm_ret:\n    ret\n\n\ninputButtonMinus:\n    ldi tmp0, 0x0f\n");
		if(uart)
		{
			write("    rcall uartSendBlock\n");
		}
		else
		{
			write("    rcall txchar\n");
		}
		write("    rcall saveLastUserInteraction\n");
		for(int i=1; i<step.length ;++i)
		{
			write("    cpi PWM_REQ, ");
			writeObject(step[i]);
			write(" // Step ");
			writeObject(i);
			write(" to ");
			writeObject(i-1);
			write("\n    brne inputButtonMinus_NOT_");
			writeObject(i);
			write("\n    ldi PWM_REQ, ");
			writeObject(step[i-1]);
			write("\ninputButtonMinus_NOT_");
			writeObject(i);
			write(":\n");
		}
		write("    ret\n\ninputButtonPlus:\n    ldi tmp0, '+'\n");
		if(uart)
		{
			write("    rcall uartSendBlock\n");
		}
		else
		{
			write("    rcall txchar\n");
		}
		write("    rcall saveLastUserInteraction\n");
		for(int i=step.length-2; i>=0;--i)
		{
			write("    cpi PWM_REQ, ");
			writeObject(step[i]);
			write(" // Step ");
			writeObject(i);
			write(" to ");
			writeObject(i+1);
			write("\n    brne inputButtonPlus_NOT_");
			writeObject(i);
			write("\n    ldi PWM_REQ, ");
			writeObject(step[i+1]);
			write("\ninputButtonPlus_NOT_");
			writeObject(i);
			write(":\n");
		}
		write("    ret\n\ninputIRMinus:\n    rcall inputButtonMinus\n    tst PWM_REQ\n    brne inputIRMinus_ret\n    ldi PWM_REQ, ");
		writeObject(step[1]);
		write("\ninputIRMinus_ret:\n    ret\n\ninputIRPlus:\n    rcall inputButtonPlus\n    ret\n\ninputIRPower:\n\trcall getSinceLastUserInteraction\n    \n    ldi ZL, lo8(pwrRepeatTimeout)\n    ldi ZH, hi8(pwrRepeatTimeout)\n    rcall comparePointerToTime\n    brlo inputIRPower_ret\n    ldi tmp0, '/'\n");
		if(uart)
		{
			write("    rcall uartSendBlock\n");
		}
		else
		{
			write("    rcall txchar\n");
		}
		write("    rcall saveLastUserInteraction\n    tst PWM_REQ\n    breq inputIRPower_on\n    ldi PWM_REQ, 0\n    rjmp inputIRPower_ret\ninputIRPower_on:\n    ldi PWM_REQ, 255\ninputIRPower_ret:\n    ret\n\n/// Save current time as last user interaction timestamp\n/// Ruins the same registers as getTime\n    .global saveLastUserInteraction\nsaveLastUserInteraction:\n\tldi ZL, lo8(lastUserInteraction)\n\tldi ZH, hi8(lastUserInteraction)\n\trcall saveTimeToPointer\n    ret\n\nsaveTimeToPointer:\n    rcall getTime\n    st Z+, tmp0\n    st Z+, tmp1\n    st Z+, tmp2\n    st Z+, tmp3\n\t\n\n\n/// checkPWMAdjust\n/// Ruins registers\n/// returns carry flag set if PWM adjust time has come\n    .global checkPWMAdjust\ncheckPWMAdjust:\n    ldi\tZL, lo8(lastPWMAdjust)\n    ldi\tZH, hi8(lastPWMAdjust)\n    rcall getTimeSincePointer\n    ldi\tZL, lo8(pwmAdjustTimeout)\n    ldi\tZH, hi8(pwmAdjustTimeout)\n    rcall comparePointerToTime\n    \n    brlo checkPWMAdjust_ret_false\n    \n    ldi ZL, lo8(lastPWMAdjust)\n    ldi ZH, hi8(lastPWMAdjust)\n    rcall saveTimeToPointer\n    sec\n    rjmp checkPWMAdjust_ret\ncheckPWMAdjust_ret_false:\n    clc\ncheckPWMAdjust_ret:\n    ret\n    \npwmAdjustTimeout:\n.byte ");
		writeObject(getByteConstant(pwmAdjustTimeout, 0));
		write("\n.byte ");
		writeObject(getByteConstant(pwmAdjustTimeout, 1));
		write("\n.byte ");
		writeObject(getByteConstant(pwmAdjustTimeout, 2));
		write("\n.byte ");
		writeObject(getByteConstant(pwmAdjustTimeout, 3));
		write("\n\n/// Get time and substract the value at SRAM pointer from it\n/// Ret is in tmp3:tmp0\ngetTimeSincePointer:\n    rcall getTime\n    \n    ld tmp4, Z+\n    sub tmp0, tmp4\n    ld tmp4, Z+\n    sbc tmp1, tmp4\n    ld tmp4, Z+\n    sbc tmp2, tmp4\n    ld tmp4, Z+\n    sbc tmp3, tmp4\n\n// Compare value in Program memory to time in tmp3:tmp0\ncomparePointerToTime:\n    lpm tmp4, Z+ // Compare to timeout\n    cp tmp0, tmp4\n    lpm tmp4, Z+\n    cpc tmp1, tmp4\n    lpm tmp4, Z+\n    cpc tmp2, tmp4\n    lpm tmp4, Z+\n    cpc tmp3, tmp4\n    ret\n\n    \n/// Check whether turn off timeout is reached?\n/// If true then turns the lamp off and saves current time as last user interaction (just to avoid overflow)\n/// Does not preserve temporary registers\n    .global checkTimeoutTurnOff\ncheckTimeoutTurnOff:\n    rcall getSinceLastUserInteraction\n    ldi ZL, lo8(turnOffTimeout)\n    ldi ZH, hi8(turnOffTimeout)\n    rcall comparePointerToTime\n    brlo checkTimeoutTurnOff_ret\n");
		if(uart)
		{
			write("    ldi tmp0, 'X'\n    rcall uartSendBlock\n");
		}
		write("    ldi PWM_REQ, 0\n    rcall saveLastUserInteraction\ncheckTimeoutTurnOff_ret:\n    ret\n\nturnOffTimeout:\n.byte ");
		writeObject(getByteConstant(turnOffTimeout, 0));
		write("\n.byte ");
		writeObject(getByteConstant(turnOffTimeout, 1));
		write("\n.byte ");
		writeObject(getByteConstant(turnOffTimeout, 2));
		write("\n.byte ");
		writeObject(getByteConstant(turnOffTimeout, 3));
		write("\n\n/// Is user interaction allowed by timeout?\n/// Interaction is disabled for a period of time\n/// Does button debouncing, button auto-repeat and IR autorepeat as well\n/// Return carry is set if user interaction is allowed\n/// Changed: SREG, \"tmp0\", \"tmp1\",\"tmp2\", \"tmp3\", \"tmp4\"\n    .global isUserInteractionAllowed\nisUserInteractionAllowed:\n");
		saveRegs();
		write("    rcall getSinceLastUserInteraction\n    \n    ldi ZL, lo8(repeatTimeout)\n    ldi ZH, hi8(repeatTimeout)\n    rcall comparePointerToTime\n    brlo isUserInteractionAllowed_no\n    sec\n    rjmp isUserInteractionAllowed_ret\nisUserInteractionAllowed_no:\n    clc\nisUserInteractionAllowed_ret:\n");
		restoreRegs();
		write("    ret\n\nrepeatTimeout:\n.byte ");
		writeObject(getByteConstant(repeatTimeout, 0));
		write("\n.byte ");
		writeObject(getByteConstant(repeatTimeout, 1));
		write("\n.byte ");
		writeObject(getByteConstant(repeatTimeout, 2));
		write("\n.byte ");
		writeObject(getByteConstant(repeatTimeout, 3));
		write("\n\npwrRepeatTimeout: // Power button has stricter repeat timeout because it is very easy to double click\n.byte ");
		writeObject(getByteConstant(pwrRepeatTimeout, 0));
		write("\n.byte ");
		writeObject(getByteConstant(pwrRepeatTimeout, 1));
		write("\n.byte ");
		writeObject(getByteConstant(pwrRepeatTimeout, 2));
		write("\n.byte ");
		writeObject(getByteConstant(pwrRepeatTimeout, 3));
		write("\n\n/// Get time spent since last user interaction (in overflow ticks)\n/// Ruins the same registers as getTime\n/// Returned value is in tmp3:tmp2:tmp1:tmp0\n    .global getSinceLastUserInteraction\ngetSinceLastUserInteraction:\n");
		saveRegs("tmp4");
		write("\tldi ZL, lo8(lastUserInteraction)\n\tldi ZH, hi8(lastUserInteraction)\n\trcall getTimeSincePointer\n");
		restoreRegs();
		write("    ret\n\n/// Read current time from timer0 overflow counter. TCNT0 is not read only the overflows\n/// 32 bits returned in: tmp3:tmp2:tmp1:tmp0\n/// status byte is ruined\n/// others are not touched\n    .global getTime\ngetTime:\n    cli\n    mov tmp0, ovf0\n    mov tmp1, ovf1\n    mov tmp2, ovf2\n    mov tmp3, ovf3\n    sei\n    ret\n\n");
		if(uart)
		{
			write("uartAppendBlock:\n    push tmp1\nuartAppendBlock_iter:\n    mov tmp1, UART_RR_N\n    cpi tmp1, 4\n    brlo uartAppendBlock_ret\n    push tmp0\n    rcall uartSendRR\n    pop tmp0\n    rjmp uartAppendBlock_iter\nuartAppendBlock_ret:\n    rcall uartAppend\n    pop tmp1    \n    ret\n\n\nuartSendBlock:\n    push tmp1\nuartSendBlock_iter:\n    mov tmp1, UART_RR_N\n    cpi tmp1, 0\n    breq uartSendBlock_ret\n    push tmp0\n    rcall uartSendRR\n    pop tmp0\n    rjmp uartSendBlock_iter\nuartSendBlock_ret:\n    tst UART_STATE\n    brne uartSendBlock_ret\n    rcall uartSend\n    pop tmp1    \n    ret\n\nuartAppend:\n    push tmp1\n    mov tmp1, UART_RR_N\n    cpi tmp1, 4\n    breq uartAppend_ret\n    cpi tmp1, 3\n    breq uartAppend_3\n    cpi tmp1, 2\n    breq uartAppend_2\n    cpi tmp1, 1\n    breq uartAppend_1\n\nuartAppend_0:\n    inc UART_RR_N\n    mov UART_RR_1, tmp0\n    rjmp uartAppend_ret\nuartAppend_1:\n    inc UART_RR_N\n    mov UART_RR_2, tmp0\n    rjmp uartAppend_ret\nuartAppend_2:\n    inc UART_RR_N\n    mov UART_RR_3, tmp0\n    rjmp uartAppend_ret\nuartAppend_3:\n    inc UART_RR_N\n    mov UART_RR_4, tmp0\n    rjmp uartAppend_ret\nuartAppend_ret:\n    pop tmp1\n    ret\n\n// Ruins tmp0!\nuartSendRR:\n    tst UART_RR_N\n    breq uartSendRR_ret\n    tst UART_STATE\n    brne uartSendRR_ret\n\n    tst UART_RR_BIT\n    brne uartSendRR_bit\n\n    ldi tmp0, 9 // Next byte\n    mov UART_RR_BIT, tmp0\n    dec UART_RR_N\n    mov UART_RR_1, UART_RR_2\n    mov UART_RR_2, UART_RR_3\n    mov UART_RR_3, UART_RR_4\n\n    rjmp uartSendRR_ret\n\nuartSendRR_bit:\n    dec UART_RR_BIT\n    tst UART_RR_BIT\n    breq uart_SendRR_NL\n    clc\n    rol UART_RR_1\n    brcs uart_SendRR_1\n    ldi tmp0, '0'\n    rjmp uart_SendRR_actually\nuart_SendRR_NL:\n    ldi tmp0, '\\n'\n    rjmp uart_SendRR_actually\nuart_SendRR_1:\n    ldi tmp0, '1'\nuart_SendRR_actually:\n    rcall uartSend\nuartSendRR_ret:\n    ret\n    \n// Send value in UART_BYTE. Usage: put 7 bit value into UART_BYTE and call this function\n// Changes:\n// * UART internal states\n// * status register\n// * tmp0\nuartSend:\n    tst UART_STATE\n    brne uartSend_ret\n    mov UART_BYTE, tmp0\n    cli\n    ldi tmp0, 9 // Start+7 data+stop\n    mov UART_STATE, tmp0 // We have 8 bits to send\n    clc // Set carry flag\n    rol UART_BYTE // Shift uart byte left - Most significant bit is not sent, LSB is start\n    ldi tmp0, ");
			writeObject(uart_divisor*2);
			write("\n    mov UART_DIVISOR, tmp0\nuartSend_ret:\n    sei\n");
		}
		write("\n");
		timerHandlerHeader();
		saveRegsIt("tmp0", "r0");
		write("// Increment ovfX 4 bytes and also save the previous value of ovf1\n    mov r0, ovf1\n    ldi tmp0, 1\n    add    ovf0, tmp0\n    ldi tmp0, 0\n    adc    ovf1, tmp0\n    adc    ovf2, tmp0\n    adc    ovf3, tmp0\n    \n");
		if(uart)
		{
			write("    tst UART_STATE\n    breq timer_no_uart // UART off\n\n    dec UART_DIVISOR\n    tst UART_DIVISOR\n    brne timer_no_uart // UART divisor not finished counting down\n    \n    dec UART_STATE // Go to next state: 0 means stop bit\n    tst UART_STATE\n    brne uart_output // UART output because we haven't reached the stop bit\n    // stop bit wait is enforced by loading a divisor value when setting up next character send\n");
		uartSetTx();
		write("    rjmp timer_no_uart\nuart_output:\n    lsr UART_BYTE // Data bit is in carry\n    brcs uart_one\n");
		uartClearTx();
		write("    rjmp uart_step\nuart_one:\n");
		uartSetTx();
		write("uart_step:\n    ldi tmp0, ");
		writeObject(uart_divisor);
		write("\n    mov UART_DIVISOR, tmp0\ntimer_no_uart:\n");
		}
		write("    // If ovf1 have changed - Every 256th overflow decreases this timeout counter\n    cp r0, ovf1\n    breq timer_ret\n    // 256 overflow cycles!\n    TST RECEIVER_TIMEOUT\n    BREQ timer_ret\n    dec RECEIVER_TIMEOUT\n    TST RECEIVER_TIMEOUT\n    BRNE timer_ret\n    ldi RECEIVER_STATE, STATE_IDLE // In case of timeout the receiver goes to idle state\n\ntimer_ret:\n");
		restoreRegs();
		write("    reti\n\n// Save the current time at state change\n// Reads time using getTime\n// Save time to ...\n// Resets the RECEIVER_TIMEOUT to 3\n// Changes: tmp0, tmp1, tmp2, tmp3, SREG\nsaveCurrentTime:\n");
		saveRegs();
		write("   rcall getTime\n   cpi RECEIVER_TIMEOUT, 3\n   brge saveCurrentTime_noreset\n   ldi RECEIVER_TIMEOUT, 3\nsaveCurrentTime_noreset:\n   mov RECEIVER_T0, tmp0\n   mov RECEIVER_T1, tmp1\n");
		restoreRegs();
		write("   ret\n\n/// Disable receiver until a timeout. Must be called after data was received or after\n.global disableReceiverTimeout\ndisableReceiverTimeout:\n   ldi RECEIVER_TIMEOUT, ");
		writeObject(250000/ovf256TMicros);
		write(" // timeout to go to STATE_IDLE ~250 millis\n   ldi RECEIVER_STATE, STATE_DISABLED\n   ret\n\n\n/// Received bit is in tmp0 (0 or 1)\n/// shift received 4 bytes, write value.\n/// Update data counter. in case of last bit received disable further input and call received handler\n.global dataReceived\ndataReceived:\n    ror tmp0 // Put bit into carry\n    rol RECEIVER_DATA_0 // Shift bit into storage\n    rol RECEIVER_DATA_1\n    rol RECEIVER_DATA_2\n    rol RECEIVER_DATA_3\n    dec RECEIVER_DATA_REMAINING\n    tst RECEIVER_DATA_REMAINING\n    BRNE dataReceived_ret\n\n    // Main program knows that data was received by RECEIVER_DATA_REMAINING==0 \n    rcall disableReceiverTimeout\n    \n    // if 0 -> rcall disableReceiverTimeout // Data received next data must wait timeout\n    // Also signal input ready so it can be processed!\ndataReceived_ret:\n    ret\n\n\n// Pin change on input\n");
		pinchangeHandlerHeader();
		saveRegsIt("tmp0", "tmp1", "tmp2", "tmp3", "ZL", "ZH");
		disablePCINT();
		write("\n    ldi RECEIVER_TIMEOUT, 3 // If not yet then do not timeout here!\n\n    sei // Pin change interrupt is disabled so this can not be re-called.\n    // Timer overflow counting must not be blocked longer than about 128 cycles!\n\n    tst RECEIVER_DATA_REMAINING\n    BRNE pcint_enabled\n    rjmp pcint_ret // RECEIVER_DATA_REMAINING 0 disables the receiver totally\npcint_enabled:\n\n    RCALL getTime\n\n    // Count time spent since last pin change tmp1:tmp0 stores the result\n    sub tmp0,RECEIVER_T0\n    sbc tmp1,RECEIVER_T1\n\n    mov tmp2, RECEIVER_STATE   // Addresses are auto-multipled by 2 in case of ROM address\n");
		startSwitch("pcint_", "tmp2", "tmp3");
		write("\n");
		caseValue("STATE_IDLE");
		write("    ldi RECEIVER_STATE, STATE_START_HIGH // Independent of T we assume this is a start edge\n");
		caseValue("STATE_START_HIGH");
		rangeCheckStart();
		write("    rcall disableReceiverTimeout // Start HIGH is too short\n");
		range(2000);
		write("    ldi RECEIVER_STATE, STATE_START_LOW // Correct Start_HIGH signal moves us into START_LOW state\n");
		range(11000);
		write("    rcall disableReceiverTimeout // Start HIGH is too long\n");
		rangeCheckEnd();
		write("\n");
		caseValue("STATE_START_LOW");
		rangeCheckStart();
		write("    rcall disableReceiverTimeout // Signal too short\n");
		range(300);
		write("    ldi tmp0, 32 // Set awaited number of bits\n    mov RECEIVER_DATA_REMAINING, tmp0\n    ldi tmp0, 0 // Clear data receiver registers\n    mov RECEIVER_DATA_0, tmp0\n    mov RECEIVER_DATA_1, tmp0\n    mov RECEIVER_DATA_2, tmp0\n    mov RECEIVER_DATA_3, tmp0\n    ldi RECEIVER_STATE, STATE_DATA_HIGH // Await first bit\n");
		range(11000);
		write("    rcall disableReceiverTimeout // Signal too long\n");
		rangeCheckEnd();
		write("\n");
		caseValue("STATE_DATA_HIGH");
		rangeCheckStart();
		write("    rcall disableReceiverTimeout // Invalid signal length\n");
		range(300);
		write("    // Valid length of data HIGH - go to LOW sate\n    ldi RECEIVER_STATE, STATE_DATA_LOW\n");
		range(1000);
		write("    rcall disableReceiverTimeout // Invalid signal length\n");
		rangeCheckEnd();
		caseValue("STATE_DATA_LOW");
		rangeCheckStart();
		write("    rcall disableReceiverTimeout // Invalid signal length\n");
		range(300);
		write("    ldi RECEIVER_STATE, STATE_DATA_HIGH\n    ldi tmp0, 0 // Received bit\n    rcall dataReceived\n");
		range(1000);
		write("    ldi RECEIVER_STATE, STATE_DATA_HIGH\n    ldi tmp0, 1  // Received bit\n    rcall dataReceived\n");
		range(2000);
		write("    rcall disableReceiverTimeout // Invalid signal length\n");
		rangeCheckEnd();
		caseValue("STATE_DISABLED");
		write("    // In disabled state we do not process any input. Disabled state will be left by timer timeout which moves us to the idle state\n");
		endSwitch();
		write("    // Save the last processed pin change time and clear timeout\n    rcall saveCurrentTime\npcint_ret:\n");
		enablePCINT();
		restoreRegs();
		write("    reti\n\n");
		if(!uart)
		{
			write("// Send byte in tmp0 (alias regA) with bitbang uart. Blocking call waits until send is ready\ntxchar:\t\t\t\t;transmit character in regA out the port bit\n    cli\n\tcbi\tUART_PORT,UART_TX\t\t;begin start bit\n\trcall\ttxrxbd\t\t;bit time delay\t\t\t\t// C3 + txrxbd\n\tldi\tloopC,8\t\t;8 data bits, no parity\t\t\t// C1\ntxc1:\tror\tregA\t\t;rotate bit 0 into carry\t// C1\n\tbrcs\ttxc2\t\t;branch if bit is high      // C1/ C2(if jump)\n\tcbi\tUART_PORT,UART_TX\t\t\t\t\t\t\t// C1\n\trjmp\ttxc3\t\t\t\t\t\t\t\t\t// C2\ntxc2:\tsbi\tUART_PORT,UART_TX\t\t\t\t\t\t\t\t// C1\ntxc3:\trcall\ttxrxbd\t\t;bit time delay\t\t\t// C3 + txrxbd\n\tdec\tloopC\t\t\t\t\t\t\t\t\t\t// C1\n\tbrne\ttxc1\t\t;loop until all bits done\t// C1/C2(if jump)\n\tsbi\tUART_PORT,UART_TX\t\t;begin the stop bit\n\trcall\ttxrxbd\t\t;bit time delay\n\t\t\t\t;wait another bit time before next character\n\t\t\t\t;(sends 2 stop bits)\n\trcall\ttxrxbd\t\t;bit time delay\n\tsei\n\tret\n\n;--------------------\n\t\t\t\t;bit delay, common to tx and rx routines\ntxrxbd:\tldi loopA,");
			writeObject(bdHigh);
			write("\t;coarse bit timing value // C1\ntxrx5:\tldi\tloopB,");
			writeObject(bdLow);
			write("\t;fine bit timing value   // C1\ntxrx4:\tdec\tloopB\t\t;inner loop // C1\n\tbrne\ttxrx4\t\t\t\t\t// C2 (it jump)/ C1 if exit\n// Clocks: ((loopB*3)+4-1)*loopA +1+4  (Outer loop is 4 cycles but last inner loop is shorter by one cycle and we correct that in the equatation)\n\tdec\tloopA\t\t;outer loop // C1\n\tbrne\ttxrx5               // C2 (if jump)\n\tret\n");
		}
		write("    .global __vector_default        // Note [10]\n__vector_default:\n    reti\n    .end\n");
		finish();
	}
	
	abstract protected void pinchangeHandlerHeader();
	abstract protected void uartClearTx();
	abstract protected void uartSetTx();
	abstract protected void timerHandlerHeader();
	abstract protected void setupPWMZero();
	abstract protected void setupPWMNonZero();
	abstract protected void readPinButtonMinus(String string);
	abstract protected void readPinButtonPlus(String string);
	abstract protected void setDebugLed();
	abstract protected void clearDebugLed();
	abstract protected void getPWMRegister(String string);
	abstract protected void setPWMRegister(String string);
	abstract protected void generateSetupTimer();
	abstract protected void generateInitPins();
	abstract protected void generatePinout();
	private Object getByteConstant(int repeatTimeout, int i) {
		while(i>0)
		{
			repeatTimeout>>=8;
			i--;
		}
		return "0x"+Integer.toHexString(repeatTimeout&0xFF);
	}

	@Override
	protected void finish() {
		super.finish();
		if(currentReceivedLabel!=null)
		{
			throw new RuntimeException("Current received label is not closed: "+currentReceivedLabel);
		}
	}

	private void checkReceiverEnd() {
		if(currentReceivedLabel==null)
		{
			throw new RuntimeException("There is no Current received label");
		}
		writeObject(currentReceivedLabel);
		write(":\n");
		currentReceivedLabel=null;
	}

	private void checkReceiver(String string, String patternAddress) {
		if(currentReceivedLabel!=null)
		{
			throw new RuntimeException("Current received label is not closed: "+currentReceivedLabel);
		}
		currentReceivedLabel=string;
		write("    ldi\tZL, lo8(");
		writeObject(patternAddress);
		write(")\n    ldi\tZH, hi8(");
		writeObject(patternAddress);
		write(")\n    rcall testPattern\n    brne ");
		writeObject(currentReceivedLabel);
		write("\n");
	}

	@SuppressWarnings("unused")
	private String binary(int p0) {
		String s=Integer.toBinaryString(p0);
		int l=s.length();
		for(int i=l;i<8;++i)
		{
			s="0"+s;
		}
		return s;
	}

	abstract protected void disablePCINT();

	abstract protected void enablePCINT();
}
