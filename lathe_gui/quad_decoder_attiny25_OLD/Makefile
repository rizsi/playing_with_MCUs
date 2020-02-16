

MCU=attiny25
#F_CPU=16 000 000 - 8MHz*2PLL
TARGET=quad_decoder
PROGRAMMER=usbtiny

SRCS = quad_decoder.asm

all: ${TARGET}.hex

${TARGET}.hex: ${SRCS}
	avra -o ${TARGET} -l ${TARGET}.lst ${SRCS}

burn: ${TARGET}.hex
	avrdude -p ${MCU} -c ${PROGRAMMER} -B10 -U flash:w:${TARGET}.hex:i -F -P usb

fuse:
	# 8MHz*2 PLL
	avrdude -p ${MCU} -c ${PROGRAMMER} -B10 -U lfuse:w:0xe1:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 
#	avrdude -p ${MCU} -c ${PROGRAMMER} -B10 -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 

clean:
	rm -f *.hex *.obj *.cof *.lst

