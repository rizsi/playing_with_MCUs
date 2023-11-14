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
# factory Default FUSE settings of the processor are good.
# This was not tested to work but a new ATTiny25 was installed with default fuse. But in theory this is the factory default
	avrdude -cusbtiny -p $(MCU_DUDE) -u \
                                 -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 

clean:
	rm -f $(BINARY).elf $(BINARY).disassemble.txt $(BINARY).list.txt $(BINARY).hex $(BINARY).o
