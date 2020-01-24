# Wireless sensor makefile

MCU = atmega328p
MCU_DUDE = m328p
BINARYNAME = blinky

all: ${BINARYNAME}.hex

${BINARYNAME}.hex:
	avr-gcc -o $(BINARYNAME).elf -mmcu=$(MCU) -Os -I. -Wl,-Map,$(BINARYNAME).map $(BINARYNAME).cpp
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


burn:	all
	avrdude -cusbtiny -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

fuse:
## TODO update fuses
#	avrdude -cusbtiny -p $(MCU_DUDE) -u \
#				-U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m



