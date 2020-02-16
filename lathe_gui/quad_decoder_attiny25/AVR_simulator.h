#include <stdint.h>

// AVR simulator interface

/// Registers are storeg from this address
#define ADDR_REG 0
/// Number of registers
#define N_REG 32
/// IOs are stored from this address
#define ADDR_IO 32
/// Number of IOs
#define N_IO 64
/// SRAM is started from this address
#define ADDR_SRAM (ADDR_IO+N_IO)
/// Number of SRAM bytes
#define N_SRAM 512
/// Status register masks
#define SREG_I 0b10000000
#define SREG_T 0b01000000
#define SREG_H 0b00100000
#define SREG_S 0b00010000
#define SREG_V 0b00001000
#define SREG_N 0b00000100
#define SREG_Z 0b00000010
#define SREG_C 0b00000001

/// Address of SREG within IO registers
#define SREG_IO_ADDR 0x3f
/// Address of SP within IO registers
#define SP_IO_ADDR 0x3d

// Address of PINB within IO registers
#define PINB 0x16
#define PORTB 0x18
#define DDRB 0x17
/// Number of words in the progmem
#define PROGMEM_N_WORDS 1024
/**
 * State of AVR simulator
 */
typedef struct {
	/** Program counter */
	uint32_t PC;
	/** Number of clock cycles since reset auto updated on the execution of each command.*/
	uint64_t cycle;
	/** The whole internal address space: registers, IO, SRAM */
	uint8_t ADDRESS[N_REG+N_IO+N_SRAM];
	/** Breakpoint was activated - execution function must return. */
	bool breakpointActivated;
} AVR_simulator_t;

/**
 * Generated code calls this when an address is executed which contains no command from the program.
 */
extern bool AVR_error_nosp(AVR_simulator_t * ctx, uint32_t pc);

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

#include <AVR_commands.h>


