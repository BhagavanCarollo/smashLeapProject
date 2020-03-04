import de.voidplus.leapmotion.*;
import processing.serial.*;
LeapMotion leap;
Serial myPort;
boolean leftExists = false, rightExists = false;
void setup(){
  String portName = Serial.list()[0];
  myPort = new Serial(this,portName, 9600);
  leap = new LeapMotion(this);
  //fullScreen();
 // println(Serial.list());
  size(1000,1000);
}
int isRight = 108/2, //54
isFist = isRight/3, //18
isSideThumb = 2*isFist, //36
isXn = isFist/3, //6
isXr = isXn*2, //12
isYn = isXn/3, //2
isYd = isYn*2, //4
isZi = isYn/2; //1
int lx, ly, lz, rx, ry, rz;
void draw() {
  background(0);
  fill(255);
  textSize(50);
  mDperiodic();
  for(Hand hand : leap.getHands()) {
    int gesture = getGesture(hand);
    if(hand.isLeft()) {
      if(gesture == flat) text("Movement",width/4,height/2);
      else if(gesture == fist) text("Sheild",width/4,height/2);
      else if(gesture == sideThumb) text("Grab",width/4,height/2);
      //text(hiVelL.x,width/4,height/2+50);
      //text(hiVelL.y,width/4,height/2+100);
      //text(hiVelL.z,width/4,height/2+150);
      int dataMail = 0;
      if(gesture == fist) dataMail+=isFist;
      if(gesture == sideThumb) dataMail+=isSideThumb;
      if(lx == 0) dataMail+=isXn;
      if(lx == 1) dataMail+=isXr;
      if(ly == 0) dataMail+=isYn;
      if(ly == 1) dataMail+=isYd;
      if(lz == 1) dataMail+=isZi;
      sendData(dataMail+1);
      leftExists = true;
    } else {
      if(gesture == flat) text("Tilt",2*width/3,height/2);
      else if(gesture == fist) text("Smash",2*width/3,height/2);
      else if(gesture == sideThumb) text("Special",2*width/3,height/2);
      //text(hiVelR.x,2*width/3,height/2+50);
      //text(hiVelR.y,2*width/3,height/2+100);
      //text(hiVelR.z,2*width/3,height/2+150);
      int dataMail = isRight;
      if(gesture == fist) dataMail+=isFist;
      if(gesture == sideThumb) dataMail+=isSideThumb;
      if(rx == 0) dataMail+=isXn;
      if(rx == 1) dataMail+=isXr;
      if(ry == 0) dataMail+=isYn;
      if(ry == 1) dataMail+=isYd;
      if(rz == 1) dataMail+=isZi;
      sendData(dataMail+1);
      rightExists = true;
    }
  }
  if(!rightExists) {rx = 0; ry = 0; rz = 0; sendData(17+54);}
  if(!leftExists)  {lx = 0; ly = 0; lz = 0;sendData(17);}
  rightExists = false;
  leftExists = false;
}
void sendData(int data) {
  myPort.write(data);
  println(data);
}
