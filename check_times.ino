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
//  bool justPressedLeft = false;
  int rightHandCounter = 0;
//  bool justPressedRight = false;

  
  
  for (byte index = 0; index < 5; index++) {
    if (millis() - buttonTimes[index] > 50) {
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
    if (millis() - buttonTimes[index] > 50) {
      rightHandCounter ++;      
      if (enteredChar[index] == false){
        rightHandFinger = index - 5;
        enteredChar[index] = true;
      }
      if (rightHandCounter > 1){
        break;
      }   
    } else {
//      rightHandFinger = 5000;
      enteredChar[index] = false;
    }

  }

if (leftHandCounter != 0 || rightHandCounter != 0){
  /*
  Serial.print(leftHandCounter);
  Serial.print(" ");
  Serial.print(leftHandFinger);
  Serial.print(" ");
  Serial.print(rightHandCounter);
  Serial.print(" ");
  Serial.println(rightHandFinger);
  */
    
    if (leftHandCounter > 1 && rightHandCounter > 1){
     
      if (lastChar != "/"){
        lastChar = "/";
        Serial.println("/"); //enter
      }
    } else if (rightHandCounter > 1){
      if (lastChar != " "){
        lastChar = " ";
        Serial.print(" "); //space
      }
    } else if (leftHandCounter > 1){
      if (lastChar != "\\"){
        lastChar = "\\";
        Serial.print("\\"); //bkspc
      }
    } else if (leftHandCounter == 1 && rightHandCounter == 1){
      if (lastChar != codedChars[leftHandFinger][rightHandFinger]){
        lastChar = codedChars[leftHandFinger][rightHandFinger];
        Serial.print(codedChars[leftHandFinger][rightHandFinger]);
      }
    } else if (leftHandCounter == 0 && rightHandFinger < 1000) {
      if (lastChar != rightHandChars[rightHandFinger]){
        lastChar = rightHandChars[rightHandFinger];
        Serial.print(rightHandChars[rightHandFinger]);
      }
    } else if (rightHandCounter == 0 && leftHandFinger < 1000) {
      if (lastChar != leftHandChars[leftHandFinger]){
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

