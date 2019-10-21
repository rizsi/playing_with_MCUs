# Wireless sensor makefile

MCU = attiny2313
MCU_DUDE = t2313
BINARYNAME = wirelessensor
SRCS = ../../$(BINARYNAME).cpp ../../onewire.cpp ../../nRF24L01_radio.cpp bsp.cpp
INCLUDES = -I. -I../..

all:
	avr-gcc -o $(BINARYNAME).elf -mmcu=$(MCU) -Os $(INCLUDES) -Wl,-Map,wirelessensor.map $(SRCS)
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


burn:	all
	avrdude -cusbtiny -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

fuse:
	avrdude -cusbtiny -p $(MCU_DUDE) -u \
				-U lfuse:w:0x64:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m



