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
    if (pressed[index]) {
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
    if (pressed[index]) {
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

//"<" represents a programmed "delete" rather than a user-entered backspace
if (leftHandCounter != 0 || rightHandCounter != 0){    
    if (leftHandCounter > 1 && rightHandCounter > 1){
      if (lastChar != 102){
        byte rightPins[] = {5, 6, 7, 8, 9};
        byte leftPins[] = {0, 1, 2, 3, 4};
        
        if (!moreThanOnePressed(rightPins) || !moreThanOnePressed(leftPins)){
           Serial.print("<");
        }
        
        lastChar = "/";
        Serial.println("/"); //enter
      }
    } else if (rightHandCounter > 1){
      if (lastChar != 94 && lastChar != 106){
        byte rightPins[] = {5, 6, 7, 8, 9};
        //check if this is just residual key press from lifting fingers for enter character
        if (atLeastOneJustPressed(rightPins)){
          if (!moreThanOnePressed(rightPins)){
            Serial.print("<");
          }
          lastChar = "]";
          Serial.print("]"); //space
        }
      }
    } else if (leftHandCounter > 1){
      if (lastChar != 108){
        byte leftPins[] = {0, 1, 2, 3, 4};
        if (atLeastOneJustPressed(leftPins)){
          if (!moreThanOnePressed(leftPins)){
            Serial.print("<");
          }
          lastChar = "[";
          Serial.print("["); //bkspc
        }
      }
    }
    
    else if (leftHandCounter == 1 && rightHandCounter == 1){
      //it's impossible to press two keys at the same time, so if two keys are pressed more than 200 ms, insert a delete character
      //in order to remove the character inserted by the first pressed character
      
      if ((justPressed[leftHandFinger] && !justPressed[rightHandFinger + 5]) ||
          (!justPressed[leftHandFinger] && justPressed[rightHandFinger + 5])){
            Serial.print("<");
      }
      
      if (justPressed[leftHandFinger] || justPressed[rightHandFinger + 5]){
        lastChar = codedChars[leftHandFinger][rightHandFinger];
        Serial.print(codedChars[leftHandFinger][rightHandFinger]);
      }
      
    } else if (leftHandCounter == 0 && rightHandFinger < 1000) {
      if (justPressed[rightHandFinger + 5]){
        lastChar = rightHandChars[rightHandFinger];
        Serial.print(rightHandChars[rightHandFinger]);
      }
    } else if (rightHandCounter == 0 && leftHandFinger < 1000) {
       
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
//it's tricky to press keys entirely simultaneously
//so, to check if this is a non-simultaneous multi-key press
//we check if more than one key is flagged as "justPressed"
boolean moreThanOnePressed(byte pins[]){
  int count = 0;
  for (byte pin = 0; pin < 5; pin++){
    if (justPressed[pins[pin]]){
      count++;
      if (count > 1) {
        return true;
      }
    }
  }
  return false;
}


boolean atLeastOneJustPressed(byte pins[]){
  int count = 0;
  for (byte pin = 0; pin < 5; pin++){
    if (justPressed[pins[pin]]){
      count++;
      if (count > 0) {
        return true;
      }
    }
  }
  return false;
}

