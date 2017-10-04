//19 47 14  // vi tester med 10

// fifo kan være 0 eller 1
int fifo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 012
int fifoTemp[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 012
int fifolength = 10;
int fifoBuffer=0;
long previousMillis = 0;
long interval = 1000;           // interval at which to blink (milliseconds)

int inputPin = 2;                 //input pin for push button
int buttonState = 0;
bool flag = false;
void setup() {

  Serial.begin(9600);
  pinMode(inputPin, INPUT_PULLUP); 
}

void loop() {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    fifififo();
  }
  buttonState = digitalRead(inputPin);
  if (buttonState == HIGH) {   
    if(!flag){
      flag=true;
      //
       fifoBuffer=1;
       fifififo();
      //
    }
  }else{
    flag=false;
    
  }
}
void fifififo() {

  if(fifoBuffer==1){ // er der en rotte i fælden ?
    fifoTemp[0]=fifoBuffer;
    
     for (int i = 0; i < fifolength-1; i++) {
       fifoTemp[i]=fifo[i]; //
       
     }
     for (int i = 0; i < fifolength; i++) {
        
       fifo[i]=fifoTemp[i];
     }
     
     fifoBuffer=0;
  }else{ // hvis ikke der er en rotte i fælden så shifter vi med space
    fifoTemp[0]=fifoBuffer;
    
     for (int i = 0; i < fifolength-1; i++) {
       fifoTemp[i]=fifo[i]; //
       
     }
     for (int i = 0; i < fifolength; i++) {
        
       fifo[i]=fifoTemp[i];
     }
     
     fifoBuffer=0;
  }
  for (int i = 0; i < fifolength-1; i++) {
    Serial.print(fifo[i]);
  } 
   Serial.println(fifo[fifolength-1]);
}


