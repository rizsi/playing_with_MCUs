#define high(value) ((uint8_t)((value>>8)&0xff))
#define low(value) ((uint8_t)(value&0xff))
#define high16(value) ((uint16_t)((value>>16)&0xffff))
#define combine16(h, l) ((uint16_t)((h<<8)&0xff00)| (l&0xff))

