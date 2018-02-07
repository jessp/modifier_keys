//borrows code from https://blog.adafruit.com/2009/10/20/example-code-for-multi-button-checker-with-debouncing/


const char leftHandChars[5] = {'A', 'E', 'I', 'O', 'U'};
const char rightHandChars[5] = {'B', 'C', 'D', 'F', 'G'};

const char codedChars[3][5] = {
    {'H', 'J', 'L', 'M', 'N'}, //rightHand 0, leftHand 0 ==H
    {'P', 'Q', 'R', 'S', 'T'},
    {'V', 'W', 'X', 'Y', 'Z'}
};

int leftHandButton = 1000;
int rightHandButton = 1000;
int leftHandButtonPrev;
int rightHandButtonPrev;
  

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

unsigned long buttonTimes[NUMBUTTONS];
unsigned long buttonReleaseTimes[NUMBUTTONS];

unsigned long buttonTimesPrev[NUMBUTTONS];
byte enteredChar[NUMBUTTONS];
int leftHandFinger = 5000;
int rightHandFinger = 5000;
byte lastChar = "%";


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
  check_times();

  check_alpha();

}

