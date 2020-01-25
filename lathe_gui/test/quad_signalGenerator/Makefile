# Quad signal decoder tester makefile
.PHONY: clean fuse minicom arduino

MCU = atmega328p
MCU_DUDE = m328p
BINARYNAME = quad_signalGenerator

SRCS = quad_signalGenerator.cpp 
#../gui/lathe_gui.cpp timer1.cpp
INCLUDES = -I.

all: ${BINARYNAME}.hex

${BINARYNAME}.hex: ${SRCS}
	avr-gcc -o $(BINARYNAME).elf -mmcu=$(MCU) -Os $(INCLUDES) -Wl,-Map,$(BINARYNAME).map $(SRCS)
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


arduino:	all
	avrdude -carduino  -P /dev/ttyACM* -b115200 -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

clean:
	rm -f ${BINARYNAME}.hex
	rm -f ${BINARYNAME}.disassemble.txt
	rm -f ${BINARYNAME}.elf
	rm -f ${BINARYNAME}.map

# We are using an Arduino - fuses are not used
#fuse:
## TODO update fuses
#	avrdude -cusbtiny -p $(MCU_DUDE) -u \
#				-U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

# Launch minicom command line
minicom:
	minicom -D /dev/ttyACM0 -b 9600 -w


