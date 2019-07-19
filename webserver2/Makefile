#/home/rizsi/tmp/arduino/arduino-1.8.9/hardware/tools/avr/bin/avr-g++ -c -g -Os -w -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Wno-error=narrowing -flto -w -x c++ -E -CC -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10809 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR -o /tmp/arduino_build_879193/preproc/ctags_target_for_gcc_minus_e.cpp

#/home/rizsi/tmp/arduino/arduino-1.8.9/tools-builder/ctags/5.8-arduino11/ctags -u --language-force=c++ -f - --c++-kinds=svpf --fields=KSTtzns --line-directives /tmp/arduino_build_879193/preproc/ctags_target_for_gcc_minus_e.cpp
#Compiling sketch...

#/home/rizsi/tmp/arduino/arduino-1.8.9/hardware/tools/avr/bin/avr-g++ -c -g -Os -w -std=gnu++11 

# -Wno-error=narrowing -MMD -flto -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=10809 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR -I/home/rizsi/tmp/arduino/arduino-1.8.9/hardware/arduino/avr/cores/arduino -I/home/rizsi/.arduino15/packages/CONTROLLINO_Boards/hardware/avr/3.0.2/variants/Controllino_maxi -I/home/rizsi/tmp/arduino/arduino-1.8.9/hardware/arduino/avr/libraries/SPI/src -I/home/rizsi/tmp/arduino/arduino-1.8.9/libraries/Ethernet/src /tmp/arduino_build_879193/sketch/WebServer.ino.cpp -o /tmp/arduino_build_879193/sketch/WebServer.ino.cpp.o

#Linking everything together...
#/home/rizsi/tmp/arduino/arduino-1.8.9/hardware/tools/avr/bin/avr-gcc -w -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections,--relax -mmcu=atmega2560 -o /tmp/arduino_build_879193/WebServer.ino.elf /tmp/arduino_build_879193/sketch/WebServer.ino.cpp.o /tmp/arduino_build_879193/libraries/SPI/SPI.cpp.o /tmp/arduino_build_879193/libraries/Ethernet/Dhcp.cpp.o /tmp/arduino_build_879193/libraries/Ethernet/Dns.cpp.o /tmp/arduino_build_879193/libraries/Ethernet/Ethernet.cpp.o /tmp/arduino_build_879193/libraries/Ethernet/EthernetClient.cpp.o /tmp/arduino_build_879193/libraries/Ethernet/EthernetServer.cpp.o /tmp/arduino_build_879193/libraries/Ethernet/EthernetUdp.cpp.o /tmp/arduino_build_879193/libraries/Ethernet/socket.cpp.o /tmp/arduino_build_879193/libraries/Ethernet/utility/w5100.cpp.o /tmp/arduino_build_879193/../arduino_cache_530236/core/core_CONTROLLINO_Boards_avr_controllino_maxi_f09982f9d5f2bb1098a33f05a8e94f32.a -L/tmp/arduino_build_879193 -lm


#Sketch uses 13244 bytes (5%) of program storage space. Maximum is 253952 bytes.
#Global variables use 669 bytes (8%) of dynamic memory, leaving 7523 bytes for local variables. Maximum is 8192 bytes.


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

ARDUINOCOMPILEOPTIONS = -g -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -Os
ARDUINOCOMPILEOPTIONS += -DARDUINO=10809 -DARDUINO_AVR_MEGA2560 -DARDUINO_ARCH_AVR -DF_CPU=16000000 -mmcu=atmega2560

LINKOPTIONS = -fuse-linker-plugin

all: webserver.hex

webserver.elf:
	avr-g++ -Wl,-gc-sections,--relax $(ARDUINOCOMPILEOPTIONS) $(LINKOPTIONS) -o webserver.elf -Wl,--no-whole-archive WebServer.cpp $(SOURCES) $(INCLUDES)

webserver.hex: webserver.elf
	mkdir -p out
	avr-objcopy -j .text -j .data -O ihex webserver.elf webserver.hex

	avr-size -C --mcu=atmega2560 webserver.elf

clean:
	rm -f webserver.elf
	rm -f webserver.hex

arduino: webserver.hex
	avrdude -v -p m2560 -cwiring -b115200 -P /dev/ttyACM* -D -U flash:w:webserver.hex:i

