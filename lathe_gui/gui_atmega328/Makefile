# Lathe gui makefile
.PHONY: clean burn fuse

MCU = atmega328p
MCU_DUDE = m328p
BINARYNAME = lathe_atmega328

SRCS = bsp_atmega328.cpp ../gui/lathe_gui.cpp timer1.cpp
INCLUDES = -I. -I../gui/

all: ${BINARYNAME}.hex

${BINARYNAME}.hex: ${SRCS}
	avr-gcc -o $(BINARYNAME).elf -mmcu=$(MCU) -Os $(INCLUDES) -Wl,-Map,$(BINARYNAME).map $(SRCS)
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


burn:	all
	avrdude -cusbtiny -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

clean:
	rm -f ${BINARYNAME}.hex
	rm -f ${BINARYNAME}.disassemble.txt
	rm -f ${BINARYNAME}.elf
	rm -f ${BINARYNAME}.map

fuse:
## TODO update fuses
#	avrdude -cusbtiny -p $(MCU_DUDE) -u \
#				-U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m



