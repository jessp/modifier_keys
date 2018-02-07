void check_times()
{
  
  for (byte index = 0; index < NUMBUTTONS; index++) {
    if (!digitalRead(buttons[index])) {
      buttonTimes[index] = millis();
    } 
    
  }

  
}

void check_alpha() {
  int leftHandCounter = 0;
  int rightHandCounter = 0;


  
  
  for (byte index = 0; index < 5; index++) {
    if (millis() - buttonTimes[index] > 10) {
      leftHandCounter ++;      
      if (enteredChar[index] == false){
        leftHandFinger = index;
        enteredChar[index] = true;
      }
      if (leftHandCounter > 1){
        break;
      }    
   } else {
    enteredChar[index] = false;
   }
  }


  for (byte index = 5; index < 10; index++) {
    if (millis() - buttonTimes[index] > 10) {
      rightHandCounter ++;      
      if (enteredChar[index] == false){
        rightHandFinger = index - 5;
        enteredChar[index] = true;
      }
      if (rightHandCounter > 1){
        break;
      }   
    } else {
      enteredChar[index] = false;
    }

  }

if (leftHandCounter != 0 || rightHandCounter != 0){    
    if (leftHandCounter > 1 && rightHandCounter > 1){
     
      if (lastChar != 92){
        lastChar = "/";
        Serial.println("/"); //enter
      }
    } else if (rightHandCounter > 1){
      if (lastChar != 78){
        lastChar = " ";
        Serial.print(" "); //space
      }
    } else if (leftHandCounter > 1){
      if (lastChar != 94){
        lastChar = "\\";
        Serial.print("\\"); //bkspc
      }
    }
    
    else if (leftHandCounter == 1 && rightHandCounter == 1){
      if (lastChar != codedChars[leftHandFinger][rightHandFinger]){
        lastChar = codedChars[leftHandFinger][rightHandFinger];
        Serial.print(codedChars[leftHandFinger][rightHandFinger]);
      }
    } else if (leftHandCounter == 0 && rightHandFinger < 1000) {
        byte leftPins[5] = {0, 1, 2, 3, 4};  
        boolean any = anyTimes(leftPins);

      if (justPressed[rightHandFinger + 5]){
        lastChar = rightHandChars[rightHandFinger];
        Serial.print(rightHandChars[rightHandFinger]);
      }
    } else if (rightHandCounter == 0 && leftHandFinger < 1000) {
       byte rightPins[5] = {5, 6, 7, 8, 9};  
       boolean any = anyTimes(rightPins);

      if (justPressed[leftHandFinger]){
        lastChar = leftHandChars[leftHandFinger];
        Serial.print(leftHandChars[leftHandFinger]);
      }
    } else {
      lastChar = "%";
    }

} else {
   lastChar = "%";
}
  
}


boolean anyTimes(byte pins[]){
   for (byte pin = 0; pin < 5; pin++){
//      if (justReleased[pins[pin]]){
//        return true;
//      }
   }
  return false;
}

