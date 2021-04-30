.PHONY= test all

MCU=attiny25
#F_CPU=16 000 000 - 8MHz*2PLL
TARGET=measure_pinchange
PROGRAMMER=usbtiny

SRCS = measure_pinchange.asm

all: ${TARGET}.hex

${TARGET}.hex: ${SRCS}
	avra -o ${TARGET} -l ${TARGET}.lst -m ${TARGET}.map ${SRCS}

burn: ${TARGET}.hex
	avrdude -p ${MCU} -c ${PROGRAMMER} -B10 -U flash:w:${TARGET}.hex:i -F -P usb

pickit2: ${TARGET}.hex
	avrdude -p t25 -c pickit2 -U flash:w:${TARGET}.hex:i -F -P usb

fuse:
	# 8MHz/8 = 1MHz
	avrdude -p ${MCU} -c ${PROGRAMMER} -B10 -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 

clean:
	rm -f *.hex *.obj *.cof *.lst

