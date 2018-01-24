void check_switches()
{
  static byte previousState[NUMBUTTONS];
  static byte currentState[NUMBUTTONS];
  static long lastTime;
  byte index;


  
  if ((lastTime + DEBOUNCE) > millis()) {
    // not enough time has passed to debounce
    /*
    //but set justPressed to false so doesn't double fire
    for (index = 0; index < NUMBUTTONS; index++) { 
        if (previousState[index] == 0 && currentState[index] == 0){
          justPressed[index] = 0; 
       }
    }
    */
    return; 
  }
  // ok we have waited DEBOUNCE milliseconds, lets reset the timer
  lastTime = millis();
  
  for (index = 0; index < NUMBUTTONS; index++) { // when we start, we clear out the "just" indicators
    justReleased[index] = 0;
    justPressed[index] = 0;
     
    currentState[index] = !digitalRead(buttons[index]);   // read the button
    
    if (currentState[index] == previousState[index]) {
      if ((pressed[index] == LOW) && (currentState[index] == LOW)) {
          // just pressed
          justPressed[index] = 1;
      }
      else if ((pressed[index] == HIGH) && (currentState[index] == HIGH)) {
          // just released
          justReleased[index] = 1;
      }
      pressed[index] = !currentState[index];  // remember, digital HIGH means NOT pressed
    }
    previousState[index] = currentState[index];   // keep a running tally of the buttons

  }
  
}

