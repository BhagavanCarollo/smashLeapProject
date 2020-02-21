//PVector lastVR = new PVector(0,0,0);// what the velocity was for the last loop for the right hand -1,0,1 for x and y, 1 or 0 for x
//PVector dirR = new PVector(0,0,0);// the direction the hand is being held for the right hand, -1,0,1 for x and y, 1 or 0 for x
//PVector lastVL = new PVector(0,0,0), dirL = new PVector(0,0,0); //same but with left
//float thresholdSpeedXY;
//float thresholdSpeedZ = thresholdSpeedXY/5; // the dimensions for z are a bit wonky
//void updateDir(Hand hand) {
//  println(avgFingerSpeed(hand));
//  if(hand.isLeft()) {
//    PVector velocity = avgFingerSpeed(hand);
//    if(lastVL.x==1) {
//      if(
//    } else if(lastVL.x==-1) {
      
//    } else {
      
//    }
//  } else {
    
//  }
//}
//PVector avgFingerSpeed(Hand hand) {
//  float sumX = 0;
//  float sumY = 0;
//  float sumZ = 0;
//  int ct = 0;
//  if(hand.getFingers().size()>0){
//    for(Finger fing : hand.getFingers()) {
//      ct++;
//      PVector thing = fing.getVelocity();
//      sumX+=thing.x;
//      sumY+=thing.y;
//      sumZ+=thing.z;
//    }
//  }
//  return new PVector(sumX/ct,sumY/ct,sumZ/ct);
//}
