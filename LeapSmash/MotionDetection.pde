float xThresh= 50, yThresh = 20, zThresh = 3;
smashHand rightHand, leftHand;
  PVector hiVelL = new PVector(0,0,0);
  PVector hiVelR = new PVector(0,0,0);
void mDperiodic() {
  if(rightHand == null) rightHand = new smashHand(null,false);
  if(leftHand == null) leftHand = new smashHand(null,false);
  leftHand.exists = false;
  rightHand.exists = false;
  for(Hand hand: leap.getHands()) {
    if(hand.isLeft()) {
      leftHand.exists = true;
      leftHand.hand = hand;
    } else {
      rightHand.exists = true;
      rightHand.hand = hand;
    }
  }
  if(rightHand.exists&&rightHand.getInited())rightHand.update();
  if(leftHand.exists&&leftHand.getInited())leftHand.update();
}
