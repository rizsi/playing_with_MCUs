// Debug send a byte by waiting for send possible
void UART0_Send(uint8_t data);
// Send data as binary 0s and 1s
void UART0_Send_Bin(uint8_t data);
/// Send number in decimal format @return number of characters written
uint8_t UART0_Send_uint32(uint32_t v);
/// Send number in decimal format @return number of characters written
uint8_t UART0_Send_int32(int32_t v);
void UART0_Init();

