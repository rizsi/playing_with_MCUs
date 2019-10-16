# Wireless sensor makefile

MCU = attiny2313
MCU_DUDE = t2313
BINARYNAME = wirelessensor

all:
	avr-gcc -mmcu=$(MCU) -Os -I. -c -g -Wa,-a,-ad $(BINARYNAME).cpp >$(BINARYNAME).list.txt
	avr-gcc -mmcu=$(MCU) -Os -I. -c -g -Wa,-a,-ad onewire.cpp >onewire.list.txt
	avr-gcc -o $(BINARYNAME).elf -mmcu=$(MCU) -Os -I. -Wl,-Map,wirelessensor.map $(BINARYNAME).cpp onewire.cpp bsp.cpp nRF24L01_radio.cpp
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


burn:	all
	avrdude -cusbtiny -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

fuse:
	avrdude -cusbtiny -p $(MCU_DUDE) -u \
				-U lfuse:w:0x64:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m



