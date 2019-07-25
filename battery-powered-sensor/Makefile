

sensor.hex: sensor.elf
	avr-objcopy -j .text -j .data -O ihex sensor.elf sensor.hex
	avr-size sensor.elf

sensor.elf: sensor.cpp
	avr-g++ -mmcu=attiny2313 sensor.cpp -Os -o sensor.elf

burn:
	avrdude -c usbtiny -p attiny2313 -U flash:w:sensor.hex

clean:
	rm -f sensor.elf
	rm -f sensor.hex

