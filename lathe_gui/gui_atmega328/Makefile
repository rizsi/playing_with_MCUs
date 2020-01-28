# Lathe gui makefile
.PHONY: clean burn fuse divisors minicom

MCU = atmega328p
MCU_DUDE = m328p
BINARYNAME = lathe_atmega328

SRCS = bsp_atmega328.cpp ../gui/lathe_gui.cpp timer1.cpp debug_uart0.cpp
INCLUDES = -I. -I../gui/

all: ${BINARYNAME}.hex

${BINARYNAME}.hex: ${SRCS}
	avr-gcc -o $(BINARYNAME).elf -mmcu=$(MCU) -Os $(INCLUDES) -Wl,-Map,$(BINARYNAME).map $(SRCS)
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


burn:	all
	avrdude -cusbtiny -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

# It is possible to burn the program onto an Arduino UNO even though it is not designed for that target
arduino: all
	avrdude -carduino  -P /dev/ttyACM* -b115200 -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

clean:
	rm -f ${BINARYNAME}.hex
	rm -f ${BINARYNAME}.disassemble.txt
	rm -f ${BINARYNAME}.elf
	rm -f ${BINARYNAME}.map

divisors:	# Generate divisors mapping code from divisors values - the result was copied into the code
	javac Divisors.java
	java Divisors

# Set fuses - 8MHz internal oscillator clock
fuse:
	avrdude -cusbtiny -p $(MCU_DUDE) -u \
		-U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m 

# Launch minicom command line
minicom:
	minicom -D /dev/ttyACM0 -b 19200 -w

