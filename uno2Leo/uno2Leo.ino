

#include <Wire.h>
byte x;
char val;
void setup()
{
  x=4;
  Wire.begin(4);        // join i2c bus (address optional for master)
  Serial.begin(9600);
}

void loop()
{
   if ( Serial.available()) //recive value from proccesing
  {  // If data is available,
  val = Serial.read();         // read it and store it in val
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  }
  x = ((int)val);
 Serial.println(val);
Wire.beginTransmission(4); // transmit to device #4
//Wire.write("x is "); 
Wire.write(x);// sends x
Wire.endTransmission(); // stop transmitting
Serial.println(x);


delay(50);
  
}
