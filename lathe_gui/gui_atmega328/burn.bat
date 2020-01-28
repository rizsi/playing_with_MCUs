REM Burn Lathe GUI Main program using pickit2 into atmega328 also set up fuses for internal oscillator 8MHz
echo Burn Lathe GUI Main program using pickit2 into atmega328
avrdude.exe -cpickit2 -p m328p -u -U flash:w:lathe_atmega328.hex
avrdude.exe -cpickit2 -p m328p -u -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m

