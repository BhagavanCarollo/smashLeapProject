class smashHand {
  int x,y,z,//-1 to 1
  xnStreak=0, ynStreak = 0;
  boolean xPaused = true, yPaused = true;
  PVector lastVel = new PVector(0,0,0);
  boolean isLeft, inited, exists, first;
  Hand hand;
  PVector lastPos = new PVector(0,0,0);
  PVector currPos = new PVector(0,0,0);
  PVector vel = new PVector(0,0,0); //velocity per 0.0166 seconds
  smashHand(Hand hand, boolean exists) {
    this.hand = hand;
    inited = false;
    this.exists = exists;
    first = true;
  }
  boolean getInited() {
    if(hand.getTimeVisible()>=3) {
      if(inited == false) first = true;
      inited = true;
      isLeft = hand.isLeft();
    } else inited = false;
    return inited;
  }
  void update() {
    lastPos = clone(currPos);
    currPos = clone(hand.getPosition());
    PVector hiVel = hiVelL;
    println(hand.getPosition());
    println(lastPos);
    println("~");
    lastVel.x = vel.x;
    lastVel.y = vel.y;
    lastVel.z = vel.z;
    vel.x = currPos.x-lastPos.x;
    vel.y = currPos.y-lastPos.y; 
    vel.z = currPos.z-lastPos.z;
    if(hand.getTimeVisible()>3.5){
      if(abs(vel.x)>abs(hiVel.x)) hiVel.x =  vel.x;
      if(abs(vel.y)>abs(hiVel.y)) hiVel.y =  vel.y;
      if(abs(vel.z)>abs(hiVel.z)) hiVel.z =  vel.z;
    }
    if(isLeft) hiVelL = hiVel;
    else hiVelR = hiVel;
    if(!first) {
      if(vel.x>xThresh && (x==-1 || (x==0 && xPaused))) {x++; xPaused = false; xnStreak = 0;}
      if(vel.y>yThresh && (y==-1 || (y==0 && yPaused))) {y++; yPaused = false; ynStreak = 0;}
      if(vel.z>zThresh && z==0) z++;
      if(vel.x<-xThresh && (x==1 || (x==0 && xPaused))) {x--; xPaused = false; xnStreak = 0;}
      if(vel.y<-yThresh && (y==1 || (y==0 && yPaused))) {y--; yPaused = false; ynStreak = 0;}
      if(vel.z<-zThresh && z==1) z--;
      if(abs(vel.x)<xThresh) xnStreak++;
      if(abs(vel.y)<yThresh) ynStreak++;
      if(xnStreak>3) xPaused = true;
      if(ynStreak>3) yPaused = true;
    } else {first = false; x = 0; y = 0; z = 0;}
    if(isLeft) {
      text(z,width/4,height/2+300);
      text(y,width/4,height/2+250);
      text(x,width/4,height/2+200);
      lx = x;
      ly = y;
      lz = z;
    } else {
      text(z,2*width/3,height/2+300);
      text(y,2*width/3,height/2+250);
      text(x,2*width/3,height/2+200);
      rx = x;
      ry = y;
      rz = z;
    }
  }
  PVector clone(PVector pv) {
    return new PVector(pv.x,pv.y,pv.z);
  }
}
