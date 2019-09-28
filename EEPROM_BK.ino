#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int address = 0;
byte value;

void setup() {
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {

  Serial.println("Entering write");
  //Serial.println(analogRead(A0));
  int val = analogRead(A0) / 4;

  Serial.print("Analog byte value = \t");
  Serial.print(val);
  Serial.println();
  Serial.println();
  EEPROM.write(address, val);

  delay(800);
  Serial.println("Entering read");
  // read a byte from the current address of the EEPROM
  value = EEPROM.read(address);

  Serial.print(address);
  Serial.print("\t");
  Serial.print(value, DEC);
  Serial.println();
  Serial.println();

  address = address + 1;
  if (address == EEPROM.length()) 
  {
    address = 0;
  }


  delay(800);

}
