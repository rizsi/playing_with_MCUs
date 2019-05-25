.PHONY: all
all: a.hex

a.out: main.c multithreading.c multithreading.h multithreading-hwavr2560.h debug.h debug.c ../../sha1/sha1.c
	avr-gcc  -mmcu=atmega2560  \
	-Wl,-Map,a.map \
	multithreading.c main.c debug.c ../../sha1/sha1.c
	avr-gcc -c -S -mmcu=atmega2560  \
	multithreading.c main.c debug.c

a.hex: Makefile a.out
	mkdir -p out
	avr-objcopy -j .text -j .data -O ihex a.out a.hex
	avr-size -C --mcu=atmega2560 a.out

clean:
	rm -f a.out
	rm -f a.hex
	rm -f a.map
	rm -f *.s
	rm -f *.o

arduino: a.hex
	avrdude -v -p m2560 -cwiring -b115200 -P /dev/ttyACM* -D -U flash:w:a.hex:i

