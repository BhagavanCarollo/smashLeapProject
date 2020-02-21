int flat = 0, fist = 1, sideThumb = 2/* sideways Thumbs up*/;
int fcth = 13;//fingers curled threshold
int toth = 550;//thumb out threshold
int getGesture(Hand hand) {
  boolean fingersCurled; //whether or not the have a fist, regardless of thumb pos
  fingersCurled = fingerTipAvg(hand).z-hand.getPosition().z<fcth;
  //fingersCurled = hand.getPosition().z-fingerTipAvg(hand).z<fcth;
  //println(hand.getPosition().z+" "+fingerTipAvg(hand).z);
  if(fingersCurled) {
    if(hand.isLeft()) {
      for(Finger fing : hand.getFingers()) {
        PVector fingv = fing.getDirection();
        float dir = atan2(fingv.x,fingv.z);
        if(fing.getPosition().x-hand.getPosition().x+dir*300/PI>toth) return sideThumb;
      }
      return fist;
    } else {
      for(Finger fing : hand.getFingers()) {
        PVector fingv = fing.getDirection();
        float dir = atan2(-fingv.x,fingv.z);
        if(hand.getPosition().x-fing.getPosition().x+dir*300/PI>toth) return sideThumb;
      }
      return fist;
    }
  }
  else return flat;
}
PVector fingerTipAvg(Hand hand) {
  int numFings = 0;
  float sumX = 0, sumY = 0, sumZ = 0;
  for(Finger fing : hand.getFingers()) {
      numFings++;
      sumX+=fing.getPosition().x;
      sumY+=fing.getPosition().y;
      sumZ+=fing.getPosition().z;
  }
  return new PVector(sumX/numFings,sumY/numFings,sumZ/numFings);
}
