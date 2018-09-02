//19 47 14  // vi tester med 10



//void setup() 
//{
//  Serial.begin(9600);
//  pinMode(inputPin, INPUT_PULLUP);
//
//   for (int i = 0; i < fifolength; i++) {
//       fifoTemp[i]=0;//
//       fifo[i]=0;//
//    }
//   delay(1000);
//     Serial.println("Hello");
//}

//void loop() 
//{
//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis > interval) {
//    previousMillis = currentMillis;
//    fifififo();
//  }
//  buttonState = digitalRead(inputPin);
//  if (buttonState == HIGH) {   
//    if(!flag){
//      flag=true;
//      //
//       fifoBuffer=1;
//       fifififo();
//      //
//    }
//  }else{
//    flag=false;
//    
//  }
//}
void fifififo() {

  for (int i = 0; i < fifolength; i++)
  {
    lastFifo[i] = fifo[i]; 
  }

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
//  for (int i = 0; i < fifolength-1; i++) {
//    Serial.print(fifo[i]);
//  } 
//   Serial.println(fifo[fifolength-1]);

//   for (int i = 0; i < fifolength; i++) {
//
//    if (fifo[i] == 1) {
//      strip.setPixelColor(i, strip.Color(20, 0, 0));
//      strip.show();
//    } else {
//      strip.setPixelColor(i, strip.Color(0, 0, 0));
//      strip.show();
//    }
//  }
}


