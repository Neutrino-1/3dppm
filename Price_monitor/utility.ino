void updateEncoder(){

  currentStateCLK = digitalRead(ENCCLK);
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ENCDT) != currentStateCLK) {
      counter --;
    } else {
      // Encoder is rotating CW so increment
      counter ++;
    }
  }
 // Serial.println(counter);
  // Remember last CLK state
  lastStateCLK = currentStateCLK;
  updateScreen = true;
}

void buttonClick()
{
  inSideMenu = !inSideMenu; 
  updateScreen = true; 
}
