

#include <Wire.h>
byte x;
char val;
void setup()
{
  x=4;
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);
}

void loop()
{
   if ( Serial.available()) //recive value from proccesing
  {  // If data is available,
  val = Serial.read();         // read it and store it in val
  }
  x = (byte)((int)val);
 Serial.println(val);
Wire.beginTransmission(9); // transmit to device #4
//Wire.write("x is "); 
Wire.write(x);// sends x
Wire.endTransmission(); // stop transmitting
Serial.println(x);


delay(50);
  
}
