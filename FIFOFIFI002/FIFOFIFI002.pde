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
boolean flag = false;
void setup() {
  //size(800, 600);
  
  
}
void keyTyped() {
  // The variable "key" always contains the value 
  // of the most recent key pressed.
  if (key == ' ' || key == '.' || key == '-') {
     fifoBuffer=1;
     fifififo();
   }
   
    
}
void draw() {

  long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    fifififo();
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
    print(fifo[i]);
  } 
    println(fifo[fifolength-1]);
}