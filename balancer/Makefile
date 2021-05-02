# Balancer mini robot makefile
.PHONY: clean burn minicom

MCU = atmega328p
MCU_DUDE = m328p
BINARYNAME = balancer
MHZ = 16mhz
F_CPU = 16000000
#DEBUG_PARAMS="-DDEBUG_EDGE_START=cbi _SFR_IO_ADDR(PINB),4" "-DDEBUG_EDGE_END=sbi _SFR_IO_ADDR(PINB),4"
DEBUG_PARAMS="-DDEBUG_EDGE_START=" "-DDEBUG_EDGE_END="


SRCS = balancer.cpp ../lathe_gui/gui_atmega328/debug_uart0.cpp sensor.cpp
ASM_SRCS = 
INCLUDES = -I. -I../lathe_gui/gui_atmega328/

all: ${BINARYNAME}.hex

${BINARYNAME}.hex: ${SRCS}
	avr-gcc -o $(BINARYNAME).elf -mmcu=$(MCU) -DF_CPU=${F_CPU} ${DEBUG_PARAMS} -O3 $(INCLUDES) -Wl,-Map,$(BINARYNAME).map $(SRCS) $(ASM_SRCS)
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


burn:	all
	avrdude -cusbtiny -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

# Burn the program into a Sparkfun Redboard (Arduino UNO clone)
arduino: all
	avrdude -carduino  -P /dev/ttyUSB* -b115200 -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

clean:
	rm -f ${BINARYNAME}.hex
	rm -f ${BINARYNAME}.disassemble.txt
	rm -f ${BINARYNAME}.elf
	rm -f ${BINARYNAME}.map

# Launch minicom command line
minicom:
	minicom -D /dev/ttyUSB0 -b 19200 -w

