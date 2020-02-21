#include <Wire.h>

#include <XInput.h>
int a = BUTTON_B, b = BUTTON_A, x = BUTTON_Y, y = BUTTON_X;
int reData = -1;
int flat = 0, fist = 1, sideThumb = 2;
void setup() {
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);           // start serial for output
   pinMode(LED_BUILTIN, OUTPUT);
   XInput.begin();
}
void loop() {
  delay(80);
}
void receiveEvent(int howMany){
  while(1 <= Wire.available()) // loop through all but the last
  {
  char c = Wire.read();    // receive byte as an integer
  Serial.println(c);         // print the integer
  }
  int x = Wire.read();
  int reData = x;
  Serial.println(x);
  sendInputs();
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);
}
boolean pressed = false;
void sendInputs() {
  if(reData>-1) {
//    XInput.setButton(a,!pressed);
//    pressed = !pressed;
    boolean isRight = (reData/54)==1;
    int gesture = reData%54/18;
    int x = reData%18/6-1;
    int y = reData%6/2-1;
    int z = reData%2;
    if(x!=0 || y!=0 || z!=0) {
      if(gesture!=flat || !isRight) XInput.setJoystick(JOY_LEFT,x*32767,y*32767);
      if(isRight) {
        if(gesture == flat) {
          XInput.setJoystick(JOY_RIGHT,x*32767,y*32767);
          if(x==0 && y==0) XInput.setButton(a,true);
          else XInput.setButton(a,false);
          XInput.setButton(b,false);
        } else if(gesture == fist) {
          XInput.setJoystick(JOY_LEFT,x*32767,y*32767);
          XInput.setButton(a,true);
          XInput.setButton(b,false);
        } else {
          XInput.setJoystick(JOY_LEFT,x*32767,y*32767);
          XInput.setButton(b,true);
        }
      } else { 
        if(gesture == flat) {
          XInput.setJoystick(JOY_LEFT,x*32767,y*32767);
          XInput.setButton(BUTTON_RB,false);
          XInput.setTrigger(TRIGGER_RIGHT, 0);
        } else if(gesture == fist) {
          XInput.setJoystick(JOY_LEFT,x*32767,y*32767);
          XInput.setButton(BUTTON_RB,false);
          XInput.setTrigger(TRIGGER_RIGHT, 255);
        } else {
          XInput.setJoystick(JOY_LEFT,x*32767,y*32767);
          XInput.setButton(BUTTON_RB, true);
          XInput.setTrigger(TRIGGER_RIGHT, 0);
        }
      }
    }
  }
}
