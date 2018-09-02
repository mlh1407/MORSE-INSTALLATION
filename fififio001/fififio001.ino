//19 47 14  // vi tester med 10

// fifo kan være 0 eller 1
const int fifolength = 80; // skal være en konstant for at sætte længden på fifo + fifoTemp
int fifo[fifolength]; // 80
int fifoTemp[fifolength]; // 80
int fifoBuffer=0;
long previousMillis = 0;
long interval = 500;           // interval at which to blink (milliseconds)

int inputPin = 2;                 //input pin for push button
int buttonState = 0;
bool flag = false;

void setup() {

  Serial.begin(9600);
  pinMode(inputPin, INPUT_PULLUP);

   for (int i = 0; i < fifolength; i++) {
       fifoTemp[i]=0;//
       fifo[i]=0;//
    }
   delay(1000);
     Serial.println("Hello");
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
       fifoTemp[i+1]=fifo[i]; //
       
     }
     for (int i = 0; i < fifolength; i++) {
        
       fifo[i]=fifoTemp[i];
     }
     
     fifoBuffer=0;
  }else{ // hvis ikke der er en rotte i fælden så shifter vi med space
    fifoTemp[0]=fifoBuffer;
    
     for (int i = 0; i < fifolength-1; i++) {
       fifoTemp[i+1]=fifo[i]; //
       
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


