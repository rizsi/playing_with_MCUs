# Quad signal decoder tester makefile
.PHONY: clean fuse minicom arduino

MCU = atmega328p
MCU_DUDE = m328p
BINARYNAME = quad_signalGenerator
RECEIVER_FOLDER = ../../quad_decoder_attiny25_custom/receiver
MHZ = 16mhz
F_CPU = 16000000
#DEBUG_PARAMS="-DDEBUG_EDGE_START=cbi _SFR_IO_ADDR(PINB),4" "-DDEBUG_EDGE_END=sbi _SFR_IO_ADDR(PINB),4"
DEBUG_PARAMS="-DDEBUG_EDGE_START=" "-DDEBUG_EDGE_END="


SRCS = quad_signalGenerator.cpp ${RECEIVER_FOLDER}/receiver.cpp
ASM_SRCS = ${RECEIVER_FOLDER}/${MHZ}/SW_RX_1.S ${RECEIVER_FOLDER}/${MHZ}/SW_RX_2.S
INCLUDES = -I. -I${RECEIVER_FOLDER}/ -I${RECEIVER_FOLDER}/${MHZ}/ -I../../gui_atmega328/

all: ${BINARYNAME}.hex

${BINARYNAME}.hex: ${SRCS}
	avr-gcc -o $(BINARYNAME).elf -DF_CPU=${F_CPU} ${DEBUG_PARAMS} -mmcu=$(MCU) -Os $(INCLUDES) -Wl,-Map,$(BINARYNAME).map $(SRCS) $(ASM_SRCS)
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


arduino:	all
	avrdude -carduino  -P /dev/ttyACM* -b115200 -p $(MCU_DUDE) -u -U flash:w:$(BINARYNAME).hex

clean:
	rm -f ${BINARYNAME}.hex
	rm -f ${BINARYNAME}.disassemble.txt
	rm -f ${BINARYNAME}.elf
	rm -f ${BINARYNAME}.map

# We are using an Arduino - fuses are not used
#fuse:
## TODO update fuses
#	avrdude -cusbtiny -p $(MCU_DUDE) -u \
#				-U lfuse:w:0x62:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

# Launch minicom command line
minicom:
	minicom -D /dev/ttyACM0 -b 19200 -w


