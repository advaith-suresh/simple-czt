# simple-czt
Sketches can be found in src folder

## Tasks To-Do
1. Match clock rate of Arduino and CZT Detector
2. ~Find out how to send 10-bit, 26-bit messages with Arduino to CZT detector~ SOLVED: We can send 2-bytes of data with chip select low. Detector throws out the remaining 6 bits of data.
3. Figure out how to send continuous clock signal in sync with SPI clock to detector