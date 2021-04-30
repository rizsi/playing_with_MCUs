#include <stdint.h>
extern "C"{
/**
 * Exact wait N cycles. Parameter is in r24 - as in avr-gcc calling convention
 * rcall, ret and 1 cycle to load the r24 on the caller side is counted.
 * So these 2 commands will use exactly 42 cycles:
 * ldi r24, 42
 * rcall exact_cycles_8
 * When using from C the generated ASM must be checked to see if additional cycles are used on the caller side
 * Minimum cycles that are possible: 20 - less cycles will result in overflow and 256+r24 cycles will be waited
 * @param cycles number of cycles to waste
 */
extern void exact_cycles_8(uint8_t cycles);
/**
; Exact wait N cycles. Parameter is in r25:r24 pair - as in avr-gcc calling convention
; rcall, ret and 2 cycles to load the r25:r24 on the caller side is counted.
; So these 3 commands will use exactly 0x4242 cycles:
; ldi r25, 0x42
; ldi r24, 0x42
; rcall exact_cycles_16
 * When using from C the generated ASM must be checked to see if additional cycles are used on the caller side
; Minimum cycles that are possible: 32 (lower values will overflow in the 1 byte arithmetics and will result in 256+r24 wait)
 * @param cycles number of cycles to waste
 */
extern void exact_cycles_16(uint16_t cycles);
}

