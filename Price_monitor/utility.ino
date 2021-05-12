ICACHE_RAM_ATTR void updateEncoder(){

  currentStateCLK = digitalRead(ENCCLK);
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
    // If the DT state is different than the CLK state then
    // the encoder is rotating CCW so decrement
    if (digitalRead(ENCDT) != currentStateCLK) {
      if(!editable)
      counter --;
      else
      filamentInfoData[counter] -= 1;
    } else {
      // Encoder is rotating CW so increment
      if(!editable)
      counter ++;
      else
      filamentInfoData[counter] += 1;
    }
  }
 // Serial.println(counter);
  // Remember last CLK state
  lastStateCLK = currentStateCLK;
  updateScreen = true;
}

void buttonForward()
{
  if(editable){
    counter++; 
    Serial.println(counter);
    }
  else if(inSideMenu){
    editable = true; 
    counter = 0;
  }
  else{
    inSideMenu = true;
  }
  updateScreen = true; 
}

void buttonBackward()
{
  if(editable){editable = false;}else{inSideMenu = false;}
  updateScreen = true; 
}

void checkIfPrintDone()
{
  //turn of the relay
}

ICACHE_RAM_ATTR void checkTicks()
{
  encoderButton.tick();
}
