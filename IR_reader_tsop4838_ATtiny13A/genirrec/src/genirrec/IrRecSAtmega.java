package genirrec;

public class IrRecSAtmega extends IrRecS {

	@Override
	protected void setup() {
		cpu_freq=8000000;
		uart=false;
		//loopBMul++;
		//loopAMul++;
	}

	@Override
	protected void generatePinout() {
		write("OUTPUT  =   PB2 // Debug output pin - flashes a LED for debug purpose\n#define UART_PORT _SFR_IO_ADDR(PORTB)\nUART_TX = PB1\nIR_INPUT = PC5 // IR input pin - PCINT13 PCI1\n\n// PWM output: OC0A, Pin 12 (12th on the left counting from 1, third from bottom), PD6\nPWM_PIN = PD6\n\nBUTTON_PLUS_PIN = PD7 // Button input pin (13th on the left counting from 1, second from bottom)\nBUTTON_MINUS_PIN = PB0 // Button input pin (14th on the left counting from 1, first from bottom)\n");
	}

	@Override
	protected void generateInitPins() {
		write("    sbi _SFR_IO_ADDR(DDRB), OUTPUT\n    cbi _SFR_IO_ADDR(PORTB), OUTPUT\n    \n    sbi _SFR_IO_ADDR(PORTB), UART_TX // Output set to 1 - this is the idle state for TTL UART\n    sbi _SFR_IO_ADDR(DDRB), UART_TX\n    \n    // Setup button input\n    \n    sbi _SFR_IO_ADDR(PORTB), BUTTON_MINUS_PIN // Pullup resistor on\n    cbi _SFR_IO_ADDR(DDRB), BUTTON_MINUS_PIN // Input\n    sbi _SFR_IO_ADDR(PORTD), BUTTON_PLUS_PIN // Pullup resistor on\n    cbi _SFR_IO_ADDR(DDRD), BUTTON_PLUS_PIN // Input\n    \n    cbi _SFR_IO_ADDR(PORTD), PWM_PIN // Set initial output to low\n    sbi _SFR_IO_ADDR(DDRD), PWM_PIN // Configure pin to output\n");
	}

	@Override
	protected void generateSetupTimer() {
		write("    ldi tmp0, _BV(TOIE0)\n    sts TIMSK0, tmp0\n    ldi tmp0, _BV(CS00)     ; tmr0:  CK/1\n    out _SFR_IO_ADDR(TCCR0B), tmp0\n    ldi tmp0, 0\n    out _SFR_IO_ADDR(TCNT0), tmp0\n");
	}

	@Override
	protected void enablePCINT() {
		write("    ldi tmp0, _BV(PCIE1)\n    sts PCICR, tmp0\n\n    ldi tmp0, _BV(PCIF1)\n    sts PCIFR, tmp0 // Clear the interrupt active flag if there was one unhandled before!\n    \n    ldi tmp0, _BV(PCINT13)\n    sts PCMSK1, tmp0\n");
	}

	@Override
	protected void setPWMRegister(String string) {
		write("    sts OCR0A, ");
		writeObject(string);
		write("\n");
	}

	@Override
	protected void getPWMRegister(String string) {
		write("    lds ");
		writeObject(string);
		write(", OCR0A\n");
	}

	@Override
	protected void setDebugLed() {
		write("    sbi _SFR_IO_ADDR(PORTB), OUTPUT\n");
	}

	@Override
	protected void clearDebugLed() {
		write("    cbi _SFR_IO_ADDR(PORTB), OUTPUT // PULSE LED - debug purpose\n");
	}

	@Override
	protected void readPinButtonMinus(String string) {
		write("    in ");
		writeObject(string);
		write(", _SFR_IO_ADDR(PINB)\n");
	}

	@Override
	protected void readPinButtonPlus(String string) {
		write("    in ");
		writeObject(string);
		write(", _SFR_IO_ADDR(PIND)\n");
	}

	@Override
	protected void setupPWMZero() {
		write("    // Normal mode WGM0[2:0]=0x0\n    // COM0A1:COM0A0 00 (OC0A disconnected)\n    ldi tmp0, 0     // Disable PWM output\n    out _SFR_IO_ADDR(TCCR0A), tmp0\n    cbi _SFR_IO_ADDR(PORTD), PWM_PIN // Set initial output to low\n");
	}

	@Override
	protected void setupPWMNonZero() {
		write("    // Fast PWM mode WGM0[2:0]=0x3\n    // COM0A1:COM0A0 10 (non inverting mode)\n    ldi tmp0, _BV(COM0A1)|_BV(WGM01)|_BV(WGM00)     // COM0A: 10 - non inverting mode WGM0[0:1]: 11 Fast PWM\n    out _SFR_IO_ADDR(TCCR0A), tmp0\n");
	}

	@Override
	protected void timerHandlerHeader() {
		write("    .global TIMER0_OVF_vect         // Note [7]\nTIMER0_OVF_vect:\n");
	}

	@Override
	protected void uartClearTx() {
		write("    cbi _SFR_IO_ADDR(PORTB), UART_TX // Output set to 0 - high\n");
	}

	@Override
	protected void uartSetTx() {
		write("    sbi _SFR_IO_ADDR(PORTB), UART_TX // Output set to 1 - low\n");
	}

	@Override
	protected void pinchangeHandlerHeader() {
		write(".global PCINT1_vect\nPCINT1_vect:\n");
	}
	
	@Override
	protected void disablePCINT() {
		write("// Disable PIN change interrupt\n    ldi tmp0, 0\n    sts PCICR, tmp0\n    ldi tmp0, _BV(PCIF1)\n    sts PCIFR, tmp0 // Clear the interrupt active flag if there was one during the first instructions of this handler!\n");
	}

}
