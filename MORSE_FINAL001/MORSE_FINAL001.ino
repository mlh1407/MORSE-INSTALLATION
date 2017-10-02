/*
 * 
 */
 
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2); // pin 2 = TX, pin 3 = RX (unused)
SoftwareSerial sendSerial(5, 4); // pin 2 = TX, pin 5 = RX (unused)

#define PIXEL_PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(107, PIXEL_PIN, NEO_RGB + NEO_KHZ400);

const long UNIT_TIME = 120; // dit duration in milliseconds

const int morseKeyPin = 8;
const int LED_PIN = 13; // lokalt visuelt feedback
const int WORD_SIZE = 6;
const int ALPHABET_SIZE = 107;
int wait = 10;
int words = 0;
bool allow = true;
char* message[WORD_SIZE]; 
char* letters[] = {
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
  "-----", "0",
  ".-.-.-", ".",
  "--..--", ",",
  "---...", ":",
  "..--..", "?",
  ".----.", "'",
  "-....-", "-",
  "-..-.", "/",
  "-.--.", "(",
  "-.--.-", ")",
  ".-..-.", "\"",
  "-...-", "="
};

int prevstate = 0;
unsigned long prevtime;
int curSentenceIndex = 0;
const int DITSLEN = 10;
char dits[DITSLEN];
int i = 0;
bool firstTime = true;
int numArrar1[]={98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,9,8,7,6,5,4,3,2,1,0};
//int numArrar1[]={96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,29,28,27,9,8,7,6,5,4,3,2,1,0};
int numArrar2[]={10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,97,98,99,100,101,102,103,104,105,106};
 

void setup()
{
  pinMode(morseKeyPin, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  prevtime = millis();
 
  Serial.begin(9600); // debug skal væk
  mySerial.begin(9600); // set up serial port for 9600 baud
  sendSerial.begin(9600); // set up serial port for 9600 baud
  delay(600); // wait for display to boot up

  //
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
    
 
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
        
       
       message[curSentenceIndex]= letters[2 * j + 1 ];
       
       curSentenceIndex++;
    }
    

  }
  for (int j = 0; j < WORD_SIZE; j++) {
    Serial.println(message[i]);
    }
  i = 0;
  if (words >= WORD_SIZE) {
    words = 0;
    curSentenceIndex=0;
    allow=false;

    sendMorseLeds();
    //return;
  } else {
    words++;
  }
}
 
void sendMorseLeds() {
  
 
 

  for (int i = 0; i < 80+2; i++) {
    strip.setPixelColor(numArrar1[i], strip.Color(30, 0, 0));
    strip.show();
    delay(wait*2);
    strip.setPixelColor(numArrar1[i-2], strip.Color(0, 0, 0));
    strip.show();
    delay(wait);
    
  }
  
  
  for(int i =0;i<WORD_SIZE;i++){
      
      Serial.println(message[i]);
     delay(wait);
  } 
  
  delay(3000);
   
   
  
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
  
  digitalWrite(LED_PIN, state ? HIGH : LOW); // debug
  
  unsigned long t = millis();
  unsigned long len = t - prevtime;

  if (prevstate != state) {
    if (prevstate) {
      if (len < 10) {
        // ignore
      } else if (len < UNIT_TIME * 2) {
        // dit
        if (i < DITSLEN - 1) {
          dits[i++] = '.';
        
          Serial.println(".");
        }
      } else {
        // dah
        if (i < DITSLEN - 1) {
          dits[i++] = '-';
        
        Serial.println("-");
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
     
       Serial.println(" ");
    }
  }
  
}
