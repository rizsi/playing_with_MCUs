# How Dare You?! makefile

MCU = attiny13a
MCU_DUDE = t13

all:
	avr-gcc -mmcu=$(MCU) -Os -c -g -Wa,-a,-ad howdareyou.c >howdareyou.list.txt
	avr-gcc -o howdareyou.elf -mmcu=$(MCU) -Os howdareyou.c
	avr-objdump -S --disassemble howdareyou.elf >howdareyou.disassemble.txt
	avr-objcopy -j .text -j .data -O ihex howdareyou.elf howdareyou.hex
	avr-size -C --mcu=$(MCU) howdareyou.elf


burn:	all
	avrdude -cusbtiny -p $(MCU_DUDE) -u -U flash:w:howdareyou.hex

fuse:
	avrdude -cusbtiny -p $(MCU_DUDE) -u \
				-U lfuse:w:0x69:m -U hfuse:w:0xf9:m


