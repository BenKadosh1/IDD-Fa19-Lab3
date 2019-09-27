// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

int redPin = 10;
int greenPin = 9;
int bluePin = 8;

#define COMMON_ANODE


void setup(void) {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  Serial.begin(9600);
  //Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    //Serial.println("Couldnt start");
    while (1);
  }
  //Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  //Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  //Serial.println("G");

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT); 
}

void loop() {
  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
  //lcd.print("X:  "); lcd.print(lis.x); 
  //lcd.print("  \tY:  "); lcd.print(lis.y); 
  //lcd.print("  \tZ:  "); lcd.print(lis.z); 

  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  
  /* Display the results (acceleration is measured in m/s^2) */
  //lcd.print("\t\tX: "); lcd.print(event.acceleration.x);
  /*
  lcd.print("X: "); lcd.print(event.acceleration.x);
  lcd.print(" Y: "); lcd.print(event.acceleration.y); 
  lcd.setCursor(0, 1);
  lcd.print("Z: "); lcd.print(event.acceleration.z); 
  lcd.print(" m/s^2 ");
  */
  //Serial.println();

  double x_accel = abs(event.acceleration.x);
  double y_accel= abs(event.acceleration.y);
  double z_accel = abs(event.acceleration.z);

  double total_accel = x_accel + y_accel + z_accel;
  
  
  double r_color = round((x_accel/total_accel)*255);
  double g_color = round((y_accel/total_accel)*255);
  double b_color = round((z_accel/total_accel)*255);

  /*
  Serial.println(x_accel);
  Serial.println(y_accel);
  Serial.println(z_accel);
  Serial.println(total_accel);
  Serial.println(r_color);
  Serial.println(g_color);
  Serial.println(b_color);
  Serial.println();
  */

  //Serial.print(total_accel, r_color, g_color, b_color);


  lcd.print("R = "); lcd.print((int)r_color);
  lcd.print(" G = "); lcd.print((int)g_color);
  
  lcd.setCursor(0, 1);
  lcd.print("B = "); lcd.print((int)b_color);
  setColor(r_color, g_color, b_color);
  delay(300);
  lcd.clear();
  lcd.setCursor(0, 0);

  /* 
  delay(1000); 
  lcd.clear();
  lcd.setCursor(0, 0);
  delay(1000);

  setColor(255, 0, 0);  // red
  delay(1000);
  setColor(0, 255, 0);  // green
  delay(1000);
  setColor(0, 0, 255);  // blue
  delay(1000);
  setColor(255, 255, 0);  // yellow
  delay(1000);  
  setColor(80, 0, 80);  // purple
  delay(1000);
  setColor(0, 255, 255);  // aqua
  delay(1000);

  //added
  setColor(0, 0, 0);  // none
  delay(1000);
  */
}


void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
