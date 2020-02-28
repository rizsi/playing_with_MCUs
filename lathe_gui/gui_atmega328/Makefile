# Lathe gui makefile
.PHONY: clean burn fuse divisors minicom

MCU = atmega328p
MCU_DUDE = m328p
BINARYNAME = lathe_atmega328
RECEIVER_FOLDER = ../quad_decoder_attiny25_custom/receiver
MHZ = 16mhz
F_CPU = 16000000
#DEBUG_PARAMS="-DDEBUG_EDGE_START=cbi _SFR_IO_ADDR(PINB),4" "-DDEBUG_EDGE_END=sbi _SFR_IO_ADDR(PINB),4"
DEBUG_PARAMS="-DDEBUG_EDGE_START=" "-DDEBUG_EDGE_END="


SRCS = bsp_atmega328.cpp ../gui/lathe_gui.cpp timer1.cpp debug_uart0.cpp ${RECEIVER_FOLDER}/receiver.cpp
ASM_SRCS = ${RECEIVER_FOLDER}/${MHZ}/SW_RX_1.S ${RECEIVER_FOLDER}/${MHZ}/SW_RX_2.S
INCLUDES = -I. -I../gui/ -I${RECEIVER_FOLDER}/${MHZ}/ -I${RECEIVER_FOLDER}/

all: ${BINARYNAME}.hex

${BINARYNAME}.hex: ${SRCS}
	avr-gcc -o $(BINARYNAME).elf -mmcu=$(MCU) -DF_CPU=${F_CPU} ${DEBUG_PARAMS} -O3 $(INCLUDES) -Wl,-Map,$(BINARYNAME).map $(SRCS) $(ASM_SRCS)
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


burn:	all
	avrdude -cusbtiny -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

# It is possible to burn the program onto an Arduino UNO even though it is not designed for that target
arduino: all
	avrdude -carduino  -P /dev/ttyACM* -b115200 -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

pickit2: all
	avrdude -cpickit2 -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex


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

