# Baby care lamp with IR remote control

This is the software and hardware design of an Arduino based IR remote control baby care lamp.

Features:

 * IR remote control using a generic Samsung TV remote control. (Other controllers can be easily trained)
 * Local button control
 * dimming with 8 steps
 * incandescent light bulb is used as light source because of its nice looking light spectrum. When dimmed the spectrum goes towards red and yellow which hopefully does not block production of melatonin.
 * salt shade to further improve niceness of the light
 * Auto turn off after 15 minutes

If you buid it the followings have to be considered:

 * Generic 12V power supply is required that can handle the power requirements of the Arduino+light bulb.
 * The current goes through the protection diode of the Arduino. This must be considered when chosing the light bulb
 * If you use a different remote control you have to train it with the help of debug parameters and Arduino Serial console. The program outputs measured values to the serial which have to be copied to the source code. (Training within the device and storing the patterns in EEPROM would be a nice improvement)
 * The modulation frequency of the IR receiver has to match the modulation frequency of the remote control. (You have to find by trial and error or by documentation.)


Arduino-IR-decoder

Arduino code for receiving IR signal using a TSOP4838. The receiver can be plugged into the Arduino directly.

Compiled with DEBUG enabled the program logs the sample patterns that can be used to calibrate your remote controller.

Signals of a simple remote controller (packed with NooElec NESDR Nano, Black...) are set up for use.

The application is a remote controlled lamp switch (with an Arduino controlled relay that turns the lamp on) that turns the lamp off at a given timeout.

