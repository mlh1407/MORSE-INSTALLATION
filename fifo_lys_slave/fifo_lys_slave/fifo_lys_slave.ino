// Turns Morse key into USB keyboard
#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    17

#define PING_STATE_RELEASED 0
#define PING_STATE_PRESSED  1

#define FIFO_LENGTH 80 // skal være en konstant for at sætte længden på fifo + fifoTemp

Adafruit_NeoPixel strip = Adafruit_NeoPixel(80, PIXEL_PIN, NEO_RGB + NEO_KHZ400);

const int led_pin  = 13;
const int ping_pin = 0;

int ping_state = PING_STATE_RELEASED;

int ping_btn;

const int wait = 10;

int fifo[FIFO_LENGTH]; // 80
int fifoTemp[FIFO_LENGTH]; // 80
int lastFifo[FIFO_LENGTH];
int fifoInput = 0;
long previousMillis = 0;
long blink_interval = 50;  // interval at which to blink (milliseconds)

void setup() 
{
  Serial.begin(9600);

  pinMode(led_pin, OUTPUT);
  pinMode(ping_pin, INPUT_PULLUP);
  
  fifo_init();

  strip.begin();
  strip.show();
  
  for (int i = 0; i < FIFO_LENGTH; i++) 
  {
    strip.setPixelColor(i, strip.Color(30, 0, 0));
    strip.show();
    delay(wait * 2);
    strip.setPixelColor(i, strip.Color(0, 0, 0));
    strip.show();
    delay(wait);
  }
  // 
  return;
}

void loop() 
{
  ping_btn = !digitalRead(ping_pin);

  // put your main code here, to run repeatedly:
  switch (ping_state)
  {
    case PING_STATE_RELEASED:
      if (ping_btn)
      {
        ping_state = PING_STATE_PRESSED;
        fifoInput = 1;
        digitalWrite(13, LOW);
      }
      break;
    case PING_STATE_PRESSED:
      if (!ping_btn)
      {
        ping_state = PING_STATE_RELEASED;
        digitalWrite(13, HIGH);
      }
      break;
    default:
      break;
  }
  
  update_leds();

  return;
}

void update_leds()
{
  unsigned long currentMillis = millis();

  if ((currentMillis - previousMillis) > blink_interval) {
    previousMillis = currentMillis;

    for (int i = 0; i < FIFO_LENGTH; i++) {

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

  return;
}

void fifo_init()
{
    for (int i = 0; i < FIFO_LENGTH; i++)
    {
        fifoTemp[i] = 0;
        fifo[i]     = 0;
    }
}

void fifififo() 
{
  for (int i = 0; i < FIFO_LENGTH; i++)
  {
    lastFifo[i] = fifo[i]; 
  }

  fifoTemp[0] = fifoInput;
  
  for (int i = 0; i < FIFO_LENGTH-1; i++) 
  {
    fifoTemp[i + 1] = fifo[i]; //      
  }

  for (int i = 0; i < FIFO_LENGTH; i++) 
  {    
    fifo[i] = fifoTemp[i];
  }
    
  fifoInput = 0;
}
