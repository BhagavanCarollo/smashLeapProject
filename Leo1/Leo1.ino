#include <Wire.h>

#include <XInput.h>
int a = BUTTON_B, b = BUTTON_A, x = BUTTON_Y, y = BUTTON_X;
int reData[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int reDataSize = 0;
int flat = 0, fist = 1, sideThumb = 2;
//this comment means nothing
void setup() {
  Wire.begin(9);                // join i2c bus with address #9
  //  Wire.onReceive(receiveEvent);
  Serial.begin(9600);           // start serial for output
  pinMode(LED_BUILTIN, OUTPUT);
  XInput.begin();
  for(int i = 0; i<20; i++) reData[i] = -1;
}
void loop() {
  delay(8);
  sendInputs();
}

void removeFirst(int things[]) {
  int newThing[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  for (int i = 0; i < reDataSize; i++) {
    newThing[i] = things[i + 1];
  }
  reDataSize--;
  newThing[reDataSize] = -1;
  things = newThing;
}
void addToEnd(int things[], int thing) {
  int newThing[20] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
  for (int i = 0; i < reDataSize; i++) {
    newThing[i] = things[i + 1];
  }
  if(reDataSize<=20) {
    reData[reDataSize] = thing;
    reDataSize++;
  }
}
//void receiveEvent(int howMany){
//
//  sendInputs();
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);
//}
boolean pressed = false;
void sendInputs() {
  while (Wire.available()) // loop through all but the last
  {
    char c = Wire.read();    // receive byte as an integer
    Serial.println(c);         // print the integer
    addToEnd(reData, c);
  }
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);
  while ( reDataSize > 0 ) {
    int data = reData[0];
    removeFirst(reData);
    //    XInput.setButton(a,!pressed);
    //    pressed = !pressed;
    boolean isRight = (data / 54) == 1;
    int gesture = data % 54 / 18;
    int x = data % 18 / 6 - 1;
    int y = data % 6 / 2 - 1;
    int z = data % 2;
    if(data<0)
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    else                     // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    if (x != 0 || y != 0 || z != 0) {
      if (gesture != flat || !isRight) XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
      if (isRight) {
        if (gesture == flat) {
          XInput.setJoystick(JOY_RIGHT, x * 32767, y * 32767);
          if (x == 0 && y == 0) XInput.setButton(a, true);
          else XInput.setButton(a, false);
          XInput.setButton(b, false);
        } else if (gesture == fist) {
          XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
          XInput.setButton(a, true);
          XInput.setButton(b, false);
        } else {
          XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
          XInput.setButton(b, true);
        }
      } else {
        if (gesture == flat) {
          XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
          XInput.setButton(BUTTON_RB, false);
          XInput.setTrigger(TRIGGER_RIGHT, 0);
        } else if (gesture == fist) {
          XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
          XInput.setButton(BUTTON_RB, false);
          XInput.setTrigger(TRIGGER_RIGHT, 255);
        } else {
          XInput.setJoystick(JOY_LEFT, x * 32767, y * 32767);
          XInput.setButton(BUTTON_RB, true);
          XInput.setTrigger(TRIGGER_RIGHT, 0);
        }
      }
    }
  }
}
