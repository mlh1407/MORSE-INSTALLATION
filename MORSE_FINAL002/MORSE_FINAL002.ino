String letters[] = {
  ".-", "A",
  "-...", "B",
  "-.-.", "C",
  "-..", "D",
  ".", "E",
  "..-.", "F",
  "--.", "G",
  "....", "H",
  "..", "I",
  ".---", "J",
  "-.-", "K",
  ".-..", "L",
  "--", "M",
  "-.", "N",
  "---", "O",
  ".--.", "P",
  "--.-", "Q",
  ".-.", "R",
  "...", "S",
  "-", "T",
  "..-", "U",
  "...-", "V",
  ".--", "W",
  "-..-", "X",
  "-.--", "Y",
  "--..", "Z",
  ".----", "1",
  "..---", "2",
  "...--", "3",
  "....-", "4",
  ".....", "5",
  "-....", "6",
  "--...", "7",
  "---..", "8",
  "----.", "9",
  "-----", "0"
};
const int ALPHABET_SIZE = 36; 

#include <Adafruit_NeoPixel.h>
#define PIXEL_PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(107, PIXEL_PIN, NEO_RGB + NEO_KHZ400);

const long UNIT_TIME = 120; // dit duration in milliseconds

const int morseKeyPin = 0;
 
 

int wait = 10;
int words = 0;
bool allow = true;
 


int prevstate = 0;
unsigned long prevtime;
 
const int DITSLEN = 10;
char dits[DITSLEN];
int i = 0;
bool firstTime = true;
 

void setup()
{
  pinMode(morseKeyPin, INPUT_PULLUP);
 

  prevtime = millis();
 
  Serial.begin(9600); // debug skal væk
  
  delay(600); // wait for display to boot up

  //
  strip.begin();
  strip.show(); // Initialize all pixels to "off"
    
  for (int i = 0; i < 80+2; i++) {
    strip.setPixelColor(i, strip.Color(30, 0, 0));
    strip.show();
    delay(wait*2);
    strip.setPixelColor(i-2, strip.Color(0, 0, 0));
    strip.show();
    delay(wait);
    
  }
}



void emitLetter() {

  if (firstTime) {
     
    firstTime = false;
   
  }
  dits[i] = '\0';


  String stringOne = dits;
   
  for (int j = 0; j < ALPHABET_SIZE; j++) {
 
    if (stringOne == letters[2 * j]) {
 
       Serial.println(letters[2 * j + 1]);  
       
    }
  }
  i = 0;
  sendMorseLeds();
}
 
void sendMorseLeds() {
  
  for (int i = 0; i < 80+2; i++) {
    strip.setPixelColor(i, strip.Color(30, 0, 0));
    strip.show();
    delay(wait*2);
    strip.setPixelColor(i-2, strip.Color(0, 0, 0));
    strip.show();
    delay(wait);
    
  }
  
  
 
  
  
   
   
  
  firstTime=true;
  words=0;
  allow=true;
  
  



}

void loop() {

   
  int reversed = 0;
  if (digitalRead(morseKeyPin)) {
    reversed = 0;
  } else {
    reversed = 1;
  }
  int state = reversed;
  
  
  unsigned long t = millis();
  unsigned long len = t - prevtime;

  if (prevstate != state) {
    if (prevstate) {
      if (len < 10) {
        // ignore
      } else if (len < UNIT_TIME * 2) {
        // dit
        if (i < DITSLEN - 1) {
          dits[i++] = '.' ;
        
          Serial.println('.');
        }
      } else {
        // dah
        if (i < DITSLEN - 1) {
          dits[i++] = '-';
        
        Serial.println('-');
        }
      }
    } else {
      if (len < UNIT_TIME * 2) {
        // intra-letter gap
      } else if (len < UNIT_TIME * 5.33) {
        // gap between letters
        emitLetter();
      }
    }

    prevstate = state;
    prevtime = t;
  } else {
    if (!prevstate && (i > 0) && (len >= UNIT_TIME * 5.33)) {
      // gap between words
     
       Serial.println(' ');
    }
  }
  
}
