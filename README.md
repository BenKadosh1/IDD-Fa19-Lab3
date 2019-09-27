# Data Logger (and using cool sensors!)

*A lab report by Ben Kadosh.*

## Part A.  Writing to the Serial Monitor
 
**a. Based on the readings from the serial monitor, what is the range of the analog values being read?**

The range of the analog values is 0 - 1023.
 
**b. How many bits of resolution does the analog to digital converter (ADC) on the Arduino have?**

???

## Part B. RGB LED

[RGB LED Video 1](https://www.youtube.com/watch?v=lV5BGbujLcM)

[RGB LED Video 2](https://www.youtube.com/watch?v=KqohEhZTQzo)

## Part C. Voltage Varying Sensors 
 
### 1. FSR, Flex Sensor, Photo cell, Softpot

**a. What voltage values do you see from your force sensor?**

I see values ranging from 0 when the sensor is not being touched, to at lowest 170 when minimal pressure is applied to approximately 990 when max pressure is applied.

**b. What kind of relationship does the voltage have as a function of the force applied? (e.g., linear?)**

The relationship is not linear, but rather - similar in shape to a logarithmic function. Minimal pressure will show a noticeable increase, but towards the tail end much more force must be used for small changes in voltage increase to occur. A graph depicting the relationship between voltage and force applied is below, where the y-axis is voltage readings from 0-1023 and the x-axis is for a measurement of force. 

<img src="https://github.com/BenKadosh1/IDD-Fa19-Lab3/blob/master/Voltage%20vs%20Pressure.PNG" width=800 height=450>


**c. Can you change the LED fading code values so that you get the full range of output voltages from the LED when using your FSR?**

**d. What resistance do you need to have in series to get a reasonable range of voltages from each sensor?**

With a 22k resistor I was able to get a much more reasonable range of voltages from 20 t0 1010, whereas with a 10k resistor I was able to get from 180 to 980.  

**e. What kind of relationship does the resistance have as a function of stimulus? (e.g., linear?)**

???

### 2. Accelerometer
 
**a. Include your accelerometer read-out code in your write-up.**

## Optional. Graphic Display

**Take a picture of your screen working insert it here!**

## Part D. Logging values to the EEPROM and reading them back
 
### 1. Reading and writing values to the Arduino EEPROM

**a. Does it matter what actions are assigned to which state? Why?**

**b. Why is the code here all in the setup() functions and not in the loop() functions?**
Becuase we are in essence writing to secondary memory (non-volatile memory) looping through it indefinitely would cause an overflow. Furthermore, because the amount of memory is so small, we make the desired changes once in setup to avoid overloading the secondary memory with non-terminating code in the loop() function.
**c. How many byte-sized data samples can you store on the Atmega328?**
1024 byte-size data samples, because each character occuppies one byte of memory and so there are 1024 bytes in total. 
**d. How would you get analog data from the Arduino analog pins to be byte-sized? How about analog data from the I2C devices?**
One way to cut down on memory usage would be to use data types that take up less memory. Because the analog data tends to be relatively small (0-1023) it can be stored as a byte or an unsigned char, which occupies one byte of memory, if small enough or a short int which would reduce the size to two bytes of memory. Similarly for I2C devices, the challenge here is how to handle the analog data once we have it whether from analog pins or I2C devices. So to reduce the size, we must strip padded data and use only the bare minimum amount for storing the data.
**e. Alternately, how would we store the data if it were bigger than a byte? (hint: take a look at the [EEPROMPut](https://www.arduino.cc/en/Reference/EEPROMPut) example)**
As the example shows, and as is mentioned above -- if the data is larger than a byte a short int or float could be used, as well as an array of chars or regular ints depending on the size. To maintain smaller data types and reduce memory usage as much as possible. 

**Upload your modified code that takes in analog values from your sensors and prints them back out to the Arduino Serial Monitor.**

### 2. Design your logger
 
**a. Insert here a copy of your final state diagram.**

### 3. Create your data logger!
 
**a. Record and upload a short demo video of your logger in action.**
