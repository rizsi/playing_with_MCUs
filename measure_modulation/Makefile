# Lathe gui makefile
.PHONY: clean burn fuse divisors minicom

MCU = atmega328p
MCU_DUDE = m328p
BINARYNAME = modulate
MHZ = 16mhz
F_CPU = 16000000

SRCS = modulate.c

all: ${BINARYNAME}.hex

${BINARYNAME}.hex: ${SRCS}
	avr-gcc -o $(BINARYNAME).elf -mmcu=$(MCU) -DF_CPU=${F_CPU} -O3 -Wl,-Map,$(BINARYNAME).map $(SRCS) $(ASM_SRCS)
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


# Use this target to burn the program to an Arduino UNO
arduino: all
	avrdude -carduino  -P /dev/ttyACM* -b115200 -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

clean:
	rm -f ${BINARYNAME}.hex
	rm -f ${BINARYNAME}.disassemble.txt
	rm -f ${BINARYNAME}.elf
	rm -f ${BINARYNAME}.map

