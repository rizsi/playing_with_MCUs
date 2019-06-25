
.PHONY: all clean

ARDUINOFOLDER=/home/rizsi/tmp/arduino/arduino-1.8.9
USERARDUINOFOLDER=/home/rizsi/.arduino15

INCLUDES = -I $(ARDUINOFOLDER)/hardware/arduino/avr/libraries/SPI/src
INCLUDES += -I $(ARDUINOFOLDER)/hardware/arduino/avr/cores/arduino
INCLUDES += -I $(ARDUINOFOLDER)/libraries/Ethernet/src
INCLUDES += -I $(ARDUINOFOLDER)/libraries/Ethernet/src/utility
INCLUDES += -I $(USERARDUINOFOLDER)/packages/CONTROLLINO_Boards/hardware/avr/3.0.2/variants/Controllino_maxi
INCLUDES += -I $(ARDUINOFOLDER)/hardware/arduino/avr/libraries/SPI/src

SOURCES = $(ARDUINOFOLDER)/hardware/arduino/avr/cores/arduino/*.c
SOURCES += $(ARDUINOFOLDER)/hardware/arduino/avr/cores/arduino/*.S
SOURCES += $(ARDUINOFOLDER)/hardware/arduino/avr/cores/arduino/*.cpp
SOURCES += $(ARDUINOFOLDER)/libraries/Ethernet/src/*.cpp
SOURCES += $(ARDUINOFOLDER)/libraries/Ethernet/src/utility/*.cpp
SOURCES += $(ARDUINOFOLDER)/hardware/arduino/avr/libraries/SPI/src/*.cpp

all: webserver.hex

webserver.elf:
	avr-g++ -Wl,-gc-sections -ffunction-sections -o webserver.elf -Os -fno-threadsafe-statics -DARDUINO=189 -DF_CPU=16000000 -mmcu=atmega2560 -Wl,--no-whole-archive WebServer.cpp $(SOURCES) $(INCLUDES)

webserver.hex: webserver.elf
	mkdir -p out
	avr-objcopy -j .text -j .data -O ihex webserver.elf webserver.hex

	avr-size -C --mcu=atmega2560 webserver.elf

clean:
	rm -f webserver.elf
	rm -f webserver.hex

arduino: webserver.hex
	avrdude -v -p m2560 -cwiring -b115200 -P /dev/ttyACM* -D -U flash:w:webserver.hex:i

