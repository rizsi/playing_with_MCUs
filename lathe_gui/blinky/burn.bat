REM Burn blinky using pickit2 into atmega328
echo Burn blinky using pickit2 into atmega328
avrdude.exe -cpickit2 -p m328p -u -U flash:w:blinky.hex

