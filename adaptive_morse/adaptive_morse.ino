#include <Wire.h>

// Connect button to pin 0 on the Arduino and GND.
// Connect led to pin 13 on the Arduino and GND.

#define BUTTON 2  // Button at pin 2 and GND
#define LED   13  // LED at pin 13 and GND 

void setup() 
{
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}

float DashDuration = 200.0;
boolean PrevSignal = false;
long tStartSign, tStartPause;
boolean S;
String letter = "";

void loop() 
{
  S = !digitalRead(BUTTON);

  if (S) 
  { // If button is pushed
    if (S != PrevSignal) 
    { // If buttons state has changed. From not pushed to pushed
      tStartSign = millis(); // Note the current time in milliseconds
      // A signal has begun, either a dot or a dash
      DecoderPause(tStartPause); // Determine what the pause meant
    }
    digitalWrite(LED, HIGH); // Turn LED on
  }
  else 
  { // If button is not pushed
    if (S != PrevSignal) 
    { // button goes from pushed to not pushed 
      tStartPause = millis(); // Note the current time in milliseconds
      // A pause between two signals has begun
      Decoder(tStartSign); // Determine what the signal meant
    }
    digitalWrite(LED, LOW); // Turn LED off
  }

  if (abs(millis() - tStartPause) > DashDuration * 10) 
  { // If the wait has been too long
    DecoderPause(tStartPause); // Write out letter
  }

  PrevSignal = S; // Saves the new button state
}

void Decoder(long start_time) 
{ // This function determines if the given signal from the button is 
  // a dot or a dash 
  char symbol = '?';
  long time = abs(millis() - start_time); // Duration of the current symbol (dot or dash)
  float DotDuration = DashDuration / 3.0; // Dot is three times shorter that dash

  if (time <= 2) 
    return; // Noise removal

  if (time <= DotDuration)
    symbol = '.';
  else if (time > DashDuration)  
    symbol = '-';
  else if ((time > (DashDuration + DotDuration) / 1.9) 
          && time <= DashDuration) 
    symbol = '-';
  else 
    symbol = '.';

  if (symbol == '-') 
  { // Corrects the duration of a dash
    if (time > DashDuration) 
      DashDuration++;
    if (time < DashDuration) 
      DashDuration--;
  }
  else if (symbol == '.') 
  { // Corrects the duration of a dot
    if (time > (DashDuration / 3.0)) 
      DashDuration++;
    if (time < (DashDuration / 3.0)) 
      DashDuration--;
  }

  letter += symbol; // Adds the symbol, a dot or a dash, to the string symbols that forms a letter
  //Serial.println(symbol);
}

void DecoderPause(long start_time) 
{
  if (letter == "") // If there is nothing in the letterbuffer, return 
    return;

  char symbol = '?';
  long time = abs(millis() - start_time); // Length of pause

  if (time > DashDuration - DashDuration / 40)  
  { // Short pause: Letter in the same word 
    DecoderLetter(); // Convert string of symbols to letters
    //Serial.print();
  }
  if (time > DashDuration * 2) 
  { // Long pause: Letter in a new word
    DecoderLetter(); // Convert string of symbols to letters
    // Print(" "); 
    Serial.print(" "); // Print a space
  }
  //else DecoderLetter();
  //Serial.println(symbol);
}

void DecoderLetter() 
{ // Function to determine which letter that has been sent
  static String letters[] = 
  {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
    ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "E"
  };

  int i = 0;

  while (letters[i] != "E") 
  { // Search through array until the end
    if (letters[i] == letter) 
    { // If the string of symbols has been found
      // Print((char)('A' + i));
      Serial.print((char)('A' + i)); // Print the letter as a char
      break; // End while loop
    }
    i++; // Iterate through the array
  }
  if (letters[i] == "E") 
  { // If the array has reached the end, print the symbols
    // Print(letter);
    Serial.print(letter);
  }
  letter = "";
}

void send_led_ping()
{
  return;
}

void send_keyboard_key(char key)
{
  return;
}