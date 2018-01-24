//borrows code from https://blog.adafruit.com/2009/10/20/example-code-for-multi-button-checker-with-debouncing/


const char leftHandChars[5] = {'A', 'E', 'I', 'O', 'U'};
const char rightHandChars[5] = {'B', 'C', 'D', 'F', 'G'};

const char codedChars[3][5] = {
    {'H', 'J', 'L', 'M', 'N'}, //rightHand 0, leftHand 0 ==H
    {'P', 'Q', 'R', 'S', 'T'},
    {'V', 'W', 'X', 'Y', 'Z'}
};

//
byte buttons[] = {15, 16, 17, 18, 19, 9, 10, 11, 12, 13}; 
/**
 * Adafruit Multibutton Debounce
 * https://blog.adafruit.com/2009/10/20/example-code-for-multi-button-checker-with-debouncing/
 **/

//switch stuff used in check_switches file
#define DEBOUNCE 10  // button debouncer, how many ms to debounce, 5+ ms is usually plenty

// here is where we define the buttons that we'll use. button "1" is the first, button "6" is the 6th, etc
// This handy macro lets us determine how big the array up above is, by checking the size
#define NUMBUTTONS sizeof(buttons)
// we will track if a button is just pressed, just released, or 'currently pressed' 
byte pressed[NUMBUTTONS];
byte justPressed[NUMBUTTONS];
byte justReleased[NUMBUTTONS];

void setup() 
{
  byte i;
  
  // set up serial port
  Serial.begin(9600);
  Serial.print("Button checker with ");
  Serial.print(NUMBUTTONS, DEC);
  Serial.println(" buttons");

  // pin13 LED
  pinMode(13, OUTPUT);
 
  // Make input & enable pull-up resistors on switch pins
  for (byte i=0; i < NUMBUTTONS; i++) {
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
  }
}

void loop() {
  check_switches();      // when we check the switches we'll get the current state
  /*
  for (byte i = 0; i < NUMBUTTONS; i++) {
    if (justPressed[i]) {
      Serial.print(i, DEC);
      Serial.println(" Just pressed");
       //remember, check_switches() will CLEAR the 'just pressed' flag
    }
    if (justReleased[i]) {
      Serial.print(i, DEC);
      Serial.println(" Just released");
      // remember, check_switches() will CLEAR the 'just pressed' flag
    }
    if (pressed[i]) {
      Serial.print(i, DEC);
      Serial.println(" pressed");
      // is the button pressed down at this moment
    }
  }
  */
  if (check_alphabet() != '/'){
    Serial.println(check_alphabet()); 
  }
}

char check_alphabet(){
  int leftHandButton = 1000;
  int rightHandButton = 1000;
  int leftHandButtonPrev = 1000;
  int rightHandButtonPrev = 1000;
  
  for (byte i = 0; i < 5; i++) {
    if (pressed[i]){
      leftHandButton = i;
    }
  }
  
  for (byte i = 5; i < 10; i++) {
    if (pressed[i]){
      rightHandButton = i - 5;
    }
  }

  leftHandButtonPrev = leftHandButton;
  rightHandButtonPrev = rightHandButton;
  
  if (leftHandButton != 1000 && rightHandButton != 1000){
    return codedChars[leftHandButton][rightHandButton];
  } else if (leftHandButton == 1000 && rightHandButton != 1000){
    return rightHandChars[rightHandButton];
  } else if (leftHandButton != 1000 && rightHandButton == 1000){
    return leftHandChars[leftHandButton];
  } else {
    return '/';
  }
  
}


