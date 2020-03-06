.PHONY= test all

MCU=attiny25
#F_CPU=16 000 000 - 8MHz*2PLL
TARGET=quad_decoder
PROGRAMMER=usbtiny

SRCS = quad_decoder.asm

all: test

test: test_program
	./test_program > test_report.txt

test_program: sim_gen.cpp AVR_simulator.cpp AVR_debugger.cpp
	gcc -o test_program -I. -g sim_gen.cpp AVR_simulator.cpp

# Processs hex file to generate executable simulator CPP code
sim_gen.cpp: ${TARGET}.hex
	java -jar ~/vboxshared/other/AVR-tools.jar avr-sim -hex quad_decoder.hex

# We do not regenerate it any more once it is good.
#quad_jumptable.inc: ~/vboxshared/other/AVR-tools.jar
#	java -jar ~/vboxshared/other/AVR-tools.jar generateSamplesDecoder > quad_jumptable.inc

#all: ${TARGET}.hex

${TARGET}.hex: ${SRCS} quad_jumptable.inc
	avra -o ${TARGET} -l ${TARGET}.lst -m ${TARGET}.map ${SRCS}

burn: ${TARGET}.hex
	avrdude -p ${MCU} -c ${PROGRAMMER} -B10 -U flash:w:${TARGET}.hex:i -F -P usb

pickit2: ${TARGET}.hex
	avrdude -p t25 -c pickit2 -U flash:w:${TARGET}.hex:i -F -P usb

fuse:
	# 8MHz*2 PLL
	avrdude -p ${MCU} -c ${PROGRAMMER} -B10 -U lfuse:w:0xe1:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 
#	avrdude -p ${MCU} -c ${PROGRAMMER} -B10 -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 

clean:
	rm -f *.hex *.obj *.cof *.lst

