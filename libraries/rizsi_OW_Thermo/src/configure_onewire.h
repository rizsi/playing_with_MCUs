
#define TIMER_DISABLE()   TIMSK1 &= ~_BV(TOIE1);

#define OW_TIMER_ISR() ISR(TIMER1_OVF_vect)
/// Trigger timer us - prescaler: 1
#define TIMER_TRIGGER(us, handler) timer_handler=handler; TCCR1B &=~(B00000111 <<CS10); TCCR1B |= (B00000001 << CS10); TCNT1=-((int16_t)us*16); TIFR1|=_BV(TOV1); TIMSK1 |= _BV(TOIE1)
/// Trigger timer ms - prescaler: 1024
#define TIMER_TRIGGER_MS(ms, handler) timer_handler=handler; TCCR1B &=~(B00000111 <<CS10); TCCR1B |= (B00000101 << CS10); TCNT1=-(int16_t)((int32_t)ms*16*1000/1024); TIFR1|=_BV(TOV1); TIMSK1 |= _BV(TOIE1)

// set up timer with prescaler = 1
// initialize counter
// disable overflow interrupt
#define TIMER_INIT() \
    TCCR1B &=~(B00000111 <<CS10); \
    TCCR1A&=0; \
    TCCR1B |= (B00000001 << CS10); \
   OCR1A=0xFFFF; \
   OCR1B=0xFFFF; \
    TCNT1 = 0; \
    TIMSK1 &= ~_BV(TOIE1)


#define OW_LOW()  pinMode(owPin, OUTPUT)
#define OW_RELEASE() pinMode(owPin, INPUT)
#define OW_READ() digitalRead(owPin)
