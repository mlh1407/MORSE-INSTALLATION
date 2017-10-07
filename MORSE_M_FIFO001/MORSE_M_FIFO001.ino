#include <Adafruit_NeoPixel.h>
#define PIXEL_PIN 6
//fifo
//19 47 14  // vi tester med 10

// fifo kan være 0 eller 1
const int fifolength = 80; // skal være en konstant for at sætte længden på fifo + fifoTemp
int fifo[fifolength]; // 80
int fifoTemp[fifolength]; // 80
int fifoBuffer = 0;
long previousMillis = 0;
long interval = 500;           // interval at which to blink (milliseconds)
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

  for (int i = 0; i < fifolength; i++) {
    fifoTemp[i] = 0; //
    fifo[i] = 0; //
  }

  strip.begin();
  strip.show(); // Initialize all pixels to "off"

  for (int i = 0; i < fifolength; i++) {
    strip.setPixelColor(i, strip.Color(30, 0, 0));
    strip.show();
    delay(wait * 2);
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(wait);

  }
}



void emitLetter() {


  dits[i] = '\0';


  String stringOne = dits;
  Serial.println("YAAAAAAY "+encodeMorseCode(stringOne)+" YAAAAAAY");
  for (int j = 0; j < ALPHABET_SIZE; j++) {

    if (stringOne == letters[2 * j]) {

      Serial.println(letters[2 * j + 1]);

    }
  }
  i = 0;
  fifififo();
}

void loop() {

  // hvis der er fifo indhold så kør denne ellers ikke / hvordan ?
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    fifififo();
  }
  //
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
          fifoBuffer=1;
          Serial.println('.');
        }
      } else {
        // dah
        if (i < DITSLEN - 1) {
          dits[i++] = '-';
          fifoBuffer=1;
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
void fifififo() {

  if (fifoBuffer == 1) { // er der en rotte i fælden ?
    fifoTemp[0] = fifoBuffer;

    for (int i = 0; i < fifolength - 1; i++) {
      fifoTemp[i + 1] = fifo[i]; //

    }
    for (int i = 0; i < fifolength; i++) {

      fifo[i] = fifoTemp[i];
    }

    fifoBuffer = 0;
  } else { // hvis ikke der er en rotte i fælden så shifter vi med space
    fifoTemp[0] = fifoBuffer;

    for (int i = 0; i < fifolength - 1; i++) {
      fifoTemp[i + 1] = fifo[i]; //

    }
    for (int i = 0; i < fifolength; i++) {

      fifo[i] = fifoTemp[i];
    }

    fifoBuffer = 0;
  }
  for (int i = 0; i < fifolength - 1; i++) {
    Serial.print(fifo[i]);

  }
  Serial.println(fifo[fifolength - 1]);

  for (int i = 0; i < fifolength; i++) {

    if (fifo[i] == 1) {
      strip.setPixelColor(i, strip.Color(20, 0, 0));
      strip.show();
    } else {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
      strip.show();
    }


  }
}

String encodeMorseCode(String in_string) {
    
  String TextInput = in_string;
  String MorseCode = "";
  String AlphabetArray[] = {
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", 
    "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
  };
  String MorseCodeArray[] = {
    "._", "_...", "_._.", "_..", ".", ".._.", "__.", "....", "..", ".___", "_._", "._..", "__", 
    "_.", "___", ".__.", "__._", "._.", "...", "_", ".._", "..._", ".__", "_.._", "_.__", "__.."
  };
  
    int len = sizeof(MorseCodeArray);
    for (int j=0; j<len; j++) {
      if (TextInput.equals(MorseCodeArray[j])) {
        MorseCode += AlphabetArray[j] + " " ;
      }
    }
  
  return MorseCode;
}
