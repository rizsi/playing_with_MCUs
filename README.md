# Arduino-IR-decoder

Arduino code for receiving IR signal using a TSOP4838. The receiver can be plugged into the Arduino directly.

Compiled with DEBUG enabled the program logs the sample patterns that can be used to calibrate your remote controller.

Signals of a simple remote controller (packed with NooElec NESDR Nano, Black...) are set up for use.

The application is a remote controlled lamp switch (with an Arduino controlled relay that turns the lamp on) that turns the lamp off at a given timeout.

