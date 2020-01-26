REM Burn Lathe GUI Main program using pickit2 into atmega328
echo Burn Lathe GUI Main program using pickit2 into atmega328
avrdude.exe -cpickit2 -p m328p -u -U flash:w:lathe_atmega328.hex

