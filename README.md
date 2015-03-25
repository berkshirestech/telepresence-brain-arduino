# telepresence-brain-arduino
This runs on the Arduino and controls the motors. It will receive signals from the Raspberry Pi.

List of Hardware used:

1. Arduino Uno R3 - http://www.adafruit.com/products/50

2. Stepper Motor Driver TB6560 - http://www.mpja.com/Stepmotor-Driver-3A-Max-TB6560/productinfo/31306%20MS/
    Running Driver in "Half Step Mode" (seems to work best)

3. A power supply capable of 12V at 3A - http://www.mpja.com/0-30VDC-0-3A-Variable-Benchtop-Power-Supply/productinfo/29616%20PS/

4. A stepper motor - NEMA 23 (size) with a .250 shaft. 11 ohms. Currently using a Unipolar motor (6 wire) connected in 4 wire bipolar mode. (Center taps not used.). Bipolar gives more torque, and the Stepper Motor H-Bridge Driver TB6560 supports the reversal of voltage required for Bipolar mode.
