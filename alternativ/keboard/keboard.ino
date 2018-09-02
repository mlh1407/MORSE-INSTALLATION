// Turns Morse key into USB keyboard
#include <Adafruit_NeoPixel.h>
#define PIXEL_PIN 2
#include <Bounce.h> // include de-bounce library

Adafruit_NeoPixel strip = Adafruit_NeoPixel(80, PIXEL_PIN, NEO_RGB + NEO_KHZ400);

const int led = 13; // led is connected to pin 13
const int keyPin = 4;  // morse key is connected to pin 7
// Bounce morseKey = Bounce(keyPin, 10);  // 10 ms debounce
Bounce morseKey = Bounce(keyPin, 40);  // 10 ms debounce

const unsigned long dashThresh = 120; // time threshold in ms to differentiate dots from dashes
const unsigned long letterThresh = 1000; // time threshold in ms to differentiate letter gaps
const unsigned long wordThresh = 3000; // time threshold in ms to differentiate word gaps

String inputString = ""; // initialise input string

unsigned long downTime = 0; // records the start time of state change
unsigned long upTime = 0; // records the end ttime of state change
unsigned long timeNow = 0; // records the current time 
unsigned long changeDuration = 0; // records the duration of state change
unsigned long pauseDuration = 0; // records the duration of the last pause

int pauseFlag = 0; // initilise the flag to indicate whether a pause has already been evaluated

// fifo kan være 0 eller 1t
const int fifolength = 80; // skal være en konstant for at sætte længden på fifo + fifoTemp
int fifo[fifolength]; // 107
int fifoTemp[fifolength]; // 107
int lastFifo[fifolength];
int fifoBuffer=0;
long previousMillis = 0;
long interval = 50;           // interval at which to blink (milliseconds)

// int inputPin = 2;                 //input pin for push button
// int buttonState = 0;
bool flag = false;

bool allow = true;

const int wait = 10;

void setup()
{
  Serial.begin(9600);

  pinMode(led, OUTPUT); // configure the pin connected to the led as an output
  pinMode(keyPin, INPUT_PULLUP); // configure the pin connected to the morse key as a pullup

  for (int i = 0; i < fifolength; i++) {
      fifoTemp[i]=0;//
      fifo[i]=0;//
  }

  strip.begin();
  strip.show(); // Initialize all pixels to "off"

  for (int i = 0; i < fifolength; i++) 
  {
    strip.setPixelColor(i, strip.Color(30, 0, 0));
    strip.show();
    delay(wait * 2);
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(wait);
  }
} // end of setup


void loop()
{   
  checkPause();

  // start of IF loop
  if (morseKey.update()){

    // checkPause();
    
    if (morseKey.risingEdge()) { // if input from key has gone to 1 and model is still 0, update model
      
      keyUp();
  
    } else if (morseKey.fallingEdge()) { // if input from key has gone to 0 and model is still 1, update model
      
      keyDown();
    }
  } // end of if update loop
  else {
    flag = false;
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;

    for (int i = 0; i < fifolength; i++) {

      if (fifo[i] == 1) 
      {
        strip.setPixelColor(i, strip.Color(20, 0, 0));
        // strip.show();
      } else {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
        // strip.show();
      }
    }
    
    strip.show();
    
    fifififo();
  }
} // end of loop

void keyDown()
{
    downTime = millis();
    // digitalWrite(led, HIGH); // switch LED on
}

void keyUp()
{
    upTime = millis();
    changeDuration = upTime-downTime; 
    // digitalWrite(led, LOW); // switch LED off

    if (changeDuration>0 and changeDuration<dashThresh){
      inputString = inputString + ".";
      Serial.println("DOT");

    } else if (changeDuration>=dashThresh) {
      inputString = inputString + "-";
      Serial.println("DASH");

    }

    pauseFlag = 1;
}

void checkPause()
{   
    timeNow = millis();
    pauseDuration = timeNow - upTime;

//    Serial.print(timeNow);
//    Serial.print(" ");
    // Serial.println(pauseDuration);

    if (pauseDuration >= letterThresh and pauseDuration < wordThresh and pauseFlag){ // if the preceding pause was long enough AND a pause hasn't just been evaluated, evaluate the previous inputs as a single letter
  
//      Serial.print("nyt bogstav");
//      Serial.print(" ");
//      Serial.println(pauseDuration);

      Serial.print(timeNow);
      Serial.print(" ");
      Serial.println(pauseDuration);  
      
      evaluateLetter();

      if(!flag){
        flag=true;
        //
        fifoBuffer=1;
        fifififo();
      //
      }
      
      pauseFlag = 0;
      
    } else if (pauseDuration >= wordThresh and pauseFlag) {

      Serial.println("ny ord");
      
      evaluateLetter();
      newWord();
      pauseFlag = 0;    
    }
}
// tt
void newWord()
{
  Keyboard.press(KEY_SPACE);
  Keyboard.release(KEY_SPACE);
}

void evaluateLetter()
{
  if (inputString==".-") {
      Keyboard.press(KEY_A);
      Keyboard.release(KEY_A);
  } else if (inputString=="-..."){
      Keyboard.press(KEY_B);
      Keyboard.release(KEY_B);
  } else if (inputString == "-.-."){
      Keyboard.press(KEY_C);
      Keyboard.release(KEY_C);
  } else if (inputString=="-.."){
      Keyboard.press(KEY_D);
      Keyboard.release(KEY_D);
  } else if (inputString=="."){
      Keyboard.press(KEY_E);
      Keyboard.release(KEY_E);
  } else if (inputString=="..-."){
      Keyboard.press(KEY_F);
      Keyboard.release(KEY_F);
  } else if (inputString=="--."){
      Keyboard.press(KEY_G);
      Keyboard.release(KEY_G);
  } else if (inputString=="...."){
      Keyboard.press(KEY_H);
      Keyboard.release(KEY_H);
  } else if (inputString==".."){
      Keyboard.press(KEY_I);
      Keyboard.release(KEY_I);
  } else if (inputString==".---"){
      Keyboard.press(KEY_J);
      Keyboard.release(KEY_J);
  } else if (inputString=="-.-"){
      Keyboard.press(KEY_K);
      Keyboard.release(KEY_K);
  } else if (inputString==".-.."){
      Keyboard.press(KEY_L);
      Keyboard.release(KEY_L);
  } else if (inputString=="--"){
      Keyboard.press(KEY_M);
      Keyboard.release(KEY_M);
  } else if (inputString=="-."){
      Keyboard.press(KEY_N);
      Keyboard.release(KEY_N);
  } else if (inputString=="---"){
      Keyboard.press(KEY_O);
      Keyboard.release(KEY_O);
  } else if (inputString==".--."){
      Keyboard.press(KEY_P);
      Keyboard.release(KEY_P);
  } else if (inputString=="--.-"){
      Keyboard.press(KEY_Q);
      Keyboard.release(KEY_Q);
  } else if (inputString==".-."){
      Keyboard.press(KEY_R);
      Keyboard.release(KEY_R);
  } else if (inputString=="..."){
      Keyboard.press(KEY_S);
      Keyboard.release(KEY_S);
  } else if (inputString=="-"){
      Keyboard.press(KEY_T);
      Keyboard.release(KEY_T);
  } else if (inputString=="..-"){
      Keyboard.press(KEY_U);
      Keyboard.release(KEY_U);
  } else if (inputString=="...-"){
      Keyboard.press(KEY_V);
      Keyboard.release(KEY_V);
  } else if (inputString==".--"){
      Keyboard.press(KEY_W);
      Keyboard.release(KEY_W);
  } else if (inputString=="-..-"){
      Keyboard.press(KEY_X);
      Keyboard.release(KEY_X);
  } else if (inputString=="-.--"){
      Keyboard.press(KEY_Y);
      Keyboard.release(KEY_Y);
  } else if (inputString=="--.."){
      Keyboard.press(KEY_Z);
      Keyboard.release(KEY_Z);
  } else if (inputString==".----"){
      Keyboard.press(KEY_1);
      Keyboard.release(KEY_1);
  } else if (inputString=="..---"){
      Keyboard.press(KEY_2);
      Keyboard.release(KEY_2);
  } else if (inputString=="...--"){
      Keyboard.press(KEY_3);
      Keyboard.release(KEY_3);
  } else if (inputString=="....-"){
      Keyboard.press(KEY_4);
      Keyboard.release(KEY_4);
  } else if (inputString=="....."){
      Keyboard.press(KEY_5);
      Keyboard.release(KEY_5);
  } else if (inputString=="-...."){
      Keyboard.press(KEY_6);
      Keyboard.release(KEY_6);
  } else if (inputString=="--..."){
      Keyboard.press(KEY_7);
      Keyboard.release(KEY_7);
  } else if (inputString=="---.."){
      Keyboard.press(KEY_8);
      Keyboard.release(KEY_8);
  } else if (inputString=="----."){
      Keyboard.press(KEY_9);
      Keyboard.release(KEY_9);
  } else if (inputString=="-----"){
      Keyboard.press(KEY_0);
      Keyboard.release(KEY_0);
  } else { 
//      Keyboard.press(KEY_MINUS);
//      Keyboard.release(KEY_MINUS);
  }

  inputString = ""; // re-initialise inputString ready for new letter
}
