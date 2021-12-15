all:	mega tiny
	avr-g++ -Wl,-Map,avr.map -Wl,-cref -Wa,-ahl=avr.lst -I./avr -Os -mmcu=atmega328p -o avr.elf example.cpp -S

mega:
	avr-gcc -mmcu=atmega328p -o ir-rec.elf ir-rec.S
#	avr-objcopy -j .text -j .data -O ihex avr.elf avr.hex
	avr-objdump -S ir-rec.elf
	avr-objcopy -j .text -j .data -O ihex ir-rec.elf ir-rec.hex
	avr-size -C --mcu=atmega328p ir-rec.elf

tiny:
	avr-gcc -mmcu=attiny25 -o ir-rec-tiny.elf ir-rec-tiny.S
#	avr-objdump -S ir-rec-tiny.elf
	avr-objcopy -j .text -j .data -O ihex ir-rec-tiny.elf ir-rec-tiny.hex
	avr-size -C --mcu=attiny25 ir-rec-tiny.elf


burn-mega:   mega
	avrdude -cusbtiny -p m328p -u -U flash:w:ir-rec.hex

burn-tiny:   tiny
	avrdude -cusbtiny -p t25 -u -U flash:w:ir-rec-tiny.hex

fuse-tiny:
	avrdude -cusbtiny -p t25 -u \
				-U hfuse:w:0xDF:m      \
				-U lfuse:w:0xE2:m
#				-U efuse:w:0xff:m      \
#      CK: 10

# avrdude Burn core dump - if 1022,1004,982, 962, 938, 930
# 920 works, 928

