RIZSI logger to sdcard library
==================

Write a stream of log to an SD card without filesystem with the following properties:

 * WARNING: All data on SD card is overwritten without any warning!
 * each SD card block (512 bytes) start with a //Log ...\n entry what is a valid JavaScript comment
