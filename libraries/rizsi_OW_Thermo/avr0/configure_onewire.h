#define OW_TIMER_ISR() ISR(TCA0_OVF_vect)
/// Trigger timer us - prescaler: 1
#define TIMER_TRIGGER(us, handler) timer_handler=handler; TCA0.SINGLE.CTRLA=TCA_SINGLE_CLKSEL_DIV1_gc|TCA_SINGLE_ENABLE_bm; TCA0.SINGLE.CNT=(uint16_t)(-((int16_t)us)*20); TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; TCA0.SINGLE.INTCTRL=TCA_SINGLE_OVF_bm

// TCCR1B &=~(B00000111 <<CS10); TCCR1B |= (B00000001 << CS10); TCNT1= TIFR1|=_BV(TOV1); TIMSK1 |= _BV(TOIE1)
/// Trigger timer ms - prescaler: 1024
#define TIMER_TRIGGER_MS(ms, handler) timer_handler=handler; TCA0.SINGLE.CTRLA=TCA_SINGLE_CLKSEL_DIV1024_gc|TCA_SINGLE_ENABLE_bm; TCA0.SINGLE.CNT=(uint16_t)(-((int16_t)ms)*20); TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm; TCA0.SINGLE.INTCTRL=TCA_SINGLE_OVF_bm
// TCCR1B &=~(B00000111 <<CS10); TCCR1B |= (B00000101 << CS10); TCNT1=-(int16_t)((int32_t)ms*16*1000/1024); TIFR1|=_BV(TOV1); TIMSK1 |= _BV(TOIE1)

#define TIMER_DISABLE() TCA0.SINGLE.INTCTRL=0

// set up timer with prescaler = 1
// initialize counter
// disable overflow interrupt
#define TIMER_INIT() TCA0.SINGLE.CTRLA=1; TCA0.SINGLE.INTCTRL=0


// PA4
#define OW_LOW() PORTA.OUTCLR=PIN4_bm; PORTA.DIRSET=PIN4_bm
#define OW_HIGH() PORTA.OUTSET=PIN4_bm; PORTA.DIRSET=PIN4_bm
#define OW_RELEASE() PORTA.PIN4CTRL=0; PORTA.DIRCLR=PIN4_bm
#define OW_READ() ((PORTA.IN&PIN4_bm)!=0)


#include <util/delay.h>
void DEBUG_print(const char * msg);
void DEBUG_writeNumber(uint8_t v);
//#define twiDebugMessage(X) USART0_print(X)
//#define twiDebugMessageNumber(X)  USART0_writeNumber(X)
#define DEBUG_OW_PRINT(STR) DEBUG_print(STR)
#define DEBUG_OW_NUMBER(n) DEBUG_writeNumber(n)
//#define DEBUG_OW_TICK() PORTA.DIRSET=PIN7_bm; PORTA.OUTSET=PIN7_bm; _delay_us(1); PORTA.OUTCLR=PIN7_bm
#define DEBUG_OW_TICK()

#define OW_READ_PULSE_DELAY() _delay_us(1)
#define OW_READ_REPLY_DELAY() _delay_us(1)

