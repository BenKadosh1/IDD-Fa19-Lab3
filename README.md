# Data Logger (and using cool sensors!)

*A lab report by Ben Kadosh.*

## Part A.  Writing to the Serial Monitor
 
**a. Based on the readings from the serial monitor, what is the range of the analog values being read?**

The range of the analog values is 0 - 1023.
 
**b. How many bits of resolution does the analog to digital converter (ADC) on the Arduino have?**

The Arduino is able to detect 1024 unique analog values, which we have seen to be 0 - 1023. 1024 = 2 to the 10th so there are 10 bits of resolution in the Arduino.

## Part B. RGB LED

[RGB LED Video 1](https://www.youtube.com/watch?v=lV5BGbujLcM)

[RGB LED Video 2](https://www.youtube.com/watch?v=KqohEhZTQzo)

## Part C. Voltage Varying Sensors 
 
### 1. FSR, Flex Sensor, Photo cell, Softpot

**a. What voltage values do you see from your force sensor?**

I see values ranging from 0 when the sensor is not being touched, to at lowest 170 when minimal pressure is applied to approximately 990 when max pressure is applied.

[FSR In Action](https://www.youtube.com/watch?v=rEosS_QsETw&feature=youtu.be)

**b. What kind of relationship does the voltage have as a function of the force applied? (e.g., linear?)**

The relationship is not linear, but rather - similar in shape to a logarithmic function. Minimal pressure will show a noticeable increase, but towards the tail end much more force must be used for small changes in voltage increase to occur. A graph depicting the relationship between voltage and force applied is below, where the y-axis is voltage readings from 0-1023 and the x-axis is for a measurement of force. 

<img src="https://github.com/BenKadosh1/IDD-Fa19-Lab3/blob/master/Voltage%20vs%20Pressure.PNG" width=800 height=450>


**c. Can you change the LED fading code values so that you get the full range of output voltages from the LED when using your FSR?**

Yes. Since the full range of output voltages from the FSR is 0-1023, we must find a way to translate to the full range of LED values 0-255. In order to do so, we can use the map function to change the values to get the full range of output voltages for the LED. 

**d. What resistance do you need to have in series to get a reasonable range of voltages from each sensor?**

With a 22k resistor I was able to get a much more reasonable range of voltages from 20 to 1010, whereas with a 10k resistor I was able to get from 180 to 980. 

[Softpot In Action](https://www.youtube.com/watch?v=zEQxVH3rcrE&feature=youtu.be)

[Photocell In Action](https://www.youtube.com/watch?v=H-Ps3cTD7cU&feature=youtu.be)

**e. What kind of relationship does the resistance have as a function of stimulus? (e.g., linear?)**

It appears that the relationship is linear. As can be seen with the softpot, as we slide our finger across the softpot the voltage values increase at a constant rate. We don't have to slide it a larger amount of distance to get an equal increase in voltage at any point along the surface.

### 2. Accelerometer
 
**a. Include your accelerometer read-out code in your write-up.**

[Accelerometer In Action](https://www.youtube.com/watch?v=2Tfdy9NBqa8&feature=youtu.be)

[Accelerometer Code](https://github.com/BenKadosh1/IDD-Fa19-Lab3/blob/master/acceldemo_with_LCD.ino)



[Accelerometer and LED In Action](https://www.youtube.com/watch?v=Y-yxF2pNad8&feature=youtu.be)

[Accelerometer and LED Code](https://github.com/BenKadosh1/IDD-Fa19-Lab3/blob/master/acceldemo_with_LCD_and_LED.ino)

## Optional. Graphic Display

[Graphic Display In Action](https://www.youtube.com/watch?v=u4Ng7VHn6uI&feature=youtu.be)

[Graphic Display Code](https://github.com/BenKadosh1/IDD-Fa19-Lab3/blob/master/Part_E_Code.ino)

## Part D. Logging values to the EEPROM and reading them back
 
### 1. Reading and writing values to the Arduino EEPROM

**a. Does it matter what actions are assigned to which state? Why?**

Yes it does - so long as the actions are dependent on the state. If the same actions will occur in each state then it does not matter. In the context of the code at hand, it does matter becuase the ordering of the tasks we want to accomplish matters. In order to preserve the integrity of the data, we want to ensure that we read after we write and clear after we read, as well as ensure that we write when there is data to write and read when there isn't (i.e. when the voltage is on/off high/low).

**b. Why is the code here all in the setup() functions and not in the loop() functions?**

Becuase we are in essence writing to secondary memory (non-volatile memory) looping through it indefinitely would cause an overflow. Furthermore, because the amount of memory is so small, we make the desired changes once in setup to avoid overloading the secondary memory with non-terminating code in the loop() function. In addition, we don't want to overwrite data as we loop. 

**c. How many byte-sized data samples can you store on the Atmega328?**

1024 byte-size data samples, because each character occupies one byte of memory and so there are 1024 bytes in total. 

**d. How would you get analog data from the Arduino analog pins to be byte-sized? How about analog data from the I2C devices?**

One way to cut down on memory usage would be to use data types that take up less memory. Because the analog data tends to be relatively small (0-1023) it can be stored as a byte or an unsigned char, which occupies one byte of memory, or a short int which would reduce the size to two bytes of memory. Similarly for I2C devices, the challenge here is how to handle the analog data once we have it whether from analog pins or I2C devices. So to reduce the size, we must strip padded data and use only the bare minimum amount for storing the data.

**e. Alternately, how would we store the data if it were bigger than a byte? (hint: take a look at the [EEPROMPut](https://www.arduino.cc/en/Reference/EEPROMPut) example)**

As the example shows, and as is mentioned above -- if the data is larger than a byte, a short int or float could be used, as well as an array of chars or regular ints depending on the size, By using the smaller data types that are larger than a byte, we are able to  reduce memory usage as much as possible. 

**Upload your modified code that takes in analog values from your sensors and prints them back out to the Arduino Serial Monitor.**

[Ben's EEPROM Code](https://github.com/BenKadosh1/IDD-Fa19-Lab3/blob/master/EEPROM_BK.ino)

### 2. Design your logger
 
**a. Insert here a copy of your final state diagram.**

<img src="https://github.com/BenKadosh1/IDD-Fa19-Lab3/blob/master/Final%20State%20Diagram.jpg" width=450 height=450>


### 3. Create your data logger!

Background: For my own data logger, I am using a photocell to track the intensity of light at a given time, and tracking for notable changes in light intensity over a 15 second period. The goal is to identify scenarios where there is rapid change in light that my trigger epileptic seizures. 

In order to do this, I logged the measured values from the photocell and stored them in the EEPROM. I then iterated througn the data printing it onto the LCD, and determined the change in voltage and established a threshold for what constituted a notable change and how many notable changes had to occur to trigger a warning to the user. 

[Ben's Data Logger In Action](https://www.youtube.com/watch?v=Y1YMkEicCK4&feature=youtu.be)
