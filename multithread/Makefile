.PHONY: all
all: atmega.hex pcserver

atmega.out: main.c multithreading.c multithreading.h multithreading-hwavr2560.h debug.h debug.c ../../sha1/sha1.c
	avr-gcc -o atmega.out -mmcu=atmega2560  \
	-Wl,-Map,atmega.map \
	multithreading.c main.c debug.c ../../sha1/sha1.c
	avr-gcc -c -S -mmcu=atmega2560  \
	multithreading.c main.c debug.c

atmega.hex: Makefile atmega.out
	mkdir -p out
	avr-objcopy -j .text -j .data -O ihex atmega.out atmega.hex
	avr-size -C --mcu=atmega2560 atmega.out

clean:
	rm -f pcserver
	rm -f atmega.out
	rm -f atmega.hex
	rm -f atmega.map
	rm -f *.s
	rm -f *.o

arduino: a.hex
	avrdude -v -p m2560 -cwiring -b115200 -P /dev/ttyACM* -D -U flash:w:a.hex:i

pcserver: pcserver.cpp ../../sha1/sha1.c base64.c base64.h
	g++ -o pcserver pcserver.cpp ../../sha1/sha1.c base64.c -lpthread

