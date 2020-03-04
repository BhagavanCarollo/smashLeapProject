#include <XInput.h>
#include <Wire.h>
int reData = 16, lastReData = 16;
boolean pressed = false;
int a = BUTTON_B, b = BUTTON_A, x = BUTTON_Y, y = BUTTON_X;
int flat = 0, fist = 1, sideThumb = 2;
void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);           // start serial for output
   pinMode(LED_BUILTIN, OUTPUT);
   XInput.begin();
}
void loop()
{
  delay(50);
}
void receiveEvent(int howMany){
  while(1 < Wire.available()) // loop through all but the last
  {
  char c = Wire.read();    // receive byte as an integer
//  Serial.println(c);         // print the integer
  }
  int x = Wire.read();
  reData = x-1;
//  Serial.println(reData);
//  if(x==5) {
//    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//    delay(1000);                       // wait for a second
//    digitalWrite(LED_BUILTIN, LOW);
//  }
//delay(1000);
//  if(lastReData!=reData) 
  sendInputs();
  lastReData = reData;
  reData = -1;
  delay(50);
}
void sendInputs() {
    if( reData >= 0 ) {
//        if(pressed)XInput.release(BUTTON_B);
//        else XInput.press(BUTTON_B);
//        pressed = !pressed;
//    
    boolean isRight = (reData / 54) == 1;
    int gesture = reData % 54 / 18;
    int x = reData % 18 / 6 - 1;
    int y = -(reData % 6 / 2 - 1);
    int z = reData % 2;
//    if(data<0)
//    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//    else                     // wait for a second
//    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    if (x != 0 || y != 0 || z != 0) {
      if (gesture != flat || !isRight) XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
      if (isRight) {
        if (gesture == flat) {
          XInput.setJoystick(JOY_RIGHT, x * 32767, y * 32767);
          if (x == 0 && y == 0) XInput.press(a);
          else XInput.release(a);
          XInput.release(b);
        } else if (gesture == fist) {
          XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
          XInput.press(a);
          XInput.release(b);
          XInput.setJoystick(JOY_RIGHT, 0,0);
        } else {
          XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
          XInput.press(b);
          XInput.release(a);
          XInput.setJoystick(JOY_RIGHT, 0,0);
        }
      } else {
        if (gesture == flat) {
          XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
          XInput.release(BUTTON_RB);
          XInput.setTrigger(TRIGGER_RIGHT, 0);
        } else if (gesture == fist) {
          XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
          XInput.release(BUTTON_RB);
          XInput.setTrigger(TRIGGER_RIGHT, 255);
        } else {
          XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
          XInput.press(BUTTON_RB);
          XInput.setTrigger(TRIGGER_RIGHT, 0);
        }
      }
    } else {
      if(isRight) {
        XInput.release(a);
        XInput.release(b);
        XInput.setJoystick(JOY_RIGHT, 0,0);
      } else {
          XInput.setTrigger(TRIGGER_RIGHT, 0);
          XInput.release(BUTTON_RB);
          XInput.setJoystick(JOY_LEFT, 0,0);
      }
    }
  }
}
