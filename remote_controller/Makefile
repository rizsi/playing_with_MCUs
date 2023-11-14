# How Dare You?! makefile

MCU = attiny25
MCU_DUDE = t25

BINARY=remote
SOURCE=remote.c

all:
	avr-gcc -mmcu=$(MCU) -Os -c -g -Wa,-a,-ad $(SOURCE) >$(BINARY).list.txt
	avr-gcc -o $(BINARY).elf -mmcu=$(MCU) -Os $(SOURCE)
	avr-objdump -S --disassemble $(BINARY).elf >$(BINARY).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARY).elf $(BINARY).hex
	avr-size -C --mcu=$(MCU) $(BINARY).elf


burn:	all
	avrdude -cusbtiny -p $(MCU_DUDE) -u -U flash:w:$(BINARY).hex

fuse:
	avrdude -cusbtiny -p $(MCU_DUDE) -u \
				-U lfuse:w:0x69:m -U hfuse:w:0xf9:m

clean:
	rm -f $(BINARY).elf $(BINARY).disassemble.txt $(BINARY).list.txt $(BINARY).hex $(BINARY).o
