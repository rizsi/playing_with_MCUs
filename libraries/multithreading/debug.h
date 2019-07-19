extern void init_uart();
extern void sendByte(uint8_t data);
extern void sendNumber(uint32_t data);
extern void sendStr(const char * s);
extern void dumpStack(uint16_t currentStackPointer, uint16_t nByte);

