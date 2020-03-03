# Example read sensor through custom protocol makefile
.PHONY: clean burn fuse divisors minicom

MCU = atmega328p
MCU_DUDE = m328p
BINARYNAME = example
MHZ = 16mhz
F_CPU=16000000

## Uncomment DEBUG_PARAMS so that on the receiver side the signal processing main time points are pushed out onto a debug output
#DEBUG_PARAMS="-DDEBUG_EDGE_START_WAIT=cbi _SFR_IO_ADDR(PORTB),2" "-DDEBUG_EDGE_PRELLWAIT=sbi _SFR_IO_ADDR(PORTB),2" "-DDEBUG_EDGE_START=cbi _SFR_IO_ADDR(PORTB),2" "-DDEBUG_EDGE_END=sbi _SFR_IO_ADDR(PORTB),2"


SRCS = example.cpp receiver.cpp
ASM_SRCS= ${MHZ}/SW_RX_1.S ${MHZ}/SW_RX_2.S
INCLUDES = -I. -I${MHZ}/ -I../gui/
AVR_TOOLS_JAR = ~/vboxshared/other/AVR-tools.jar

all: ${BINARYNAME}.hex

8mhz/SW_RX_1.S: Makefile ${AVR_TOOLS_JAR}
	java -jar ${AVR_TOOLS_JAR} customCommGenerator --IFACENAME SW_RX_1 --PORT PINB --PORT_PIN_INDEX 0 --outputFolder 8mhz/ --threeBaudCycles 36

8mhz/SW_RX_2.S: Makefile ${AVR_TOOLS_JAR}
	java -jar ${AVR_TOOLS_JAR} customCommGenerator --IFACENAME SW_RX_2 --PORT PIND --PORT_PIN_INDEX 4 --outputFolder 8mhz/ --threeBaudCycles 36

16mhz/SW_RX_1.S: Makefile ${AVR_TOOLS_JAR}
	java -jar ${AVR_TOOLS_JAR} customCommGenerator --IFACENAME SW_RX_1 --PORT PINB --PORT_PIN_INDEX 0 --outputFolder 16mhz/ --threeBaudCycles 72

16mhz/SW_RX_2.S: Makefile ${AVR_TOOLS_JAR}
	java -jar ${AVR_TOOLS_JAR} customCommGenerator --IFACENAME SW_RX_2 --PORT PIND --PORT_PIN_INDEX 4 --outputFolder 16mhz/ --threeBaudCycles 72


${BINARYNAME}.hex: ${SRCS} ${ASM_SRCS}
	avr-gcc -o $(BINARYNAME).elf -DF_CPU=${F_CPU} ${DEBUG_PARAMS} -mmcu=$(MCU) -O3 $(INCLUDES) -Wl,-Map,$(BINARYNAME).map $(SRCS) $(ASM_SRCS)
	avr-objdump -S --disassemble $(BINARYNAME).elf >$(BINARYNAME).disassemble.txt
	avr-objcopy -j .text -j .data -O ihex $(BINARYNAME).elf $(BINARYNAME).hex
	avr-size -C --mcu=$(MCU) $(BINARYNAME).elf

clean:
	rm -f ${BINARYNAME}.hex
	rm -f ${BINARYNAME}.disassemble.txt
	rm -f ${BINARYNAME}.elf
	rm -f ${BINARYNAME}.map
	rm -f 8mhz/*
	rm -f 16mhz/*


