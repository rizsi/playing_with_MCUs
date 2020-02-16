REM Burn Quad decoder program using pickit2 into attiny25
echo Burn Quad decoder program using pickit2 into attiny25
avrdude.exe -cpickit2 -p t25 -u -U flash:w:quad_decoder.hex

