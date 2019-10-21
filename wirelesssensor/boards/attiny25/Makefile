# Wireless sensor makefile

MCU = attiny25
MCU_DUDE = t25
FUSE = -U lfuse:w:0x62:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m
BINARYNAME = wirelessensor
SRCS = ../../$(BINARYNAME).cpp ../../onewire.cpp ../../nRF24L01_radio.cpp bsp.cpp bitbanguart.cpp
INCLUDES = -I. -I../..
AVRDUDEGENERICS = -cusbtiny -p $(MCU_DUDE)
CFLAGS += -Wl,-static
CFLAGS += -ffunction-sections
CFLAGS += -Wl,--gc-sections

all:
	avr-gcc -o $(BINARYNAME).elf -mmcu=$(MCU) -O3 -fverbose-asm $(INCLUDES) -Wl,-Map,wirelessensor.map $(CFLAGS) $(SRCS)
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf


burn:	all
	avrdude $(AVRDUDEGENERICS) -u -U flash:w:$(BINARYNAME).hex

fuse:
	avrdude $(AVRDUDEGENERICS) -u $(FUSE)
				


