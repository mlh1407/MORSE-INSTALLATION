
PFont zigBlack;
int fontSize = 50;
String morseText = "";
String words = "";
String word = "";
//19 47 14  // vi tester med 10
// fifo kan være 0 eller 1
int fifo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 012 0=mellemrum 1= prik 2 = streg
int fifoTemp[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 012
int fifolength = 10;
int fifoBuffer=0;
long previousMillis = 0;
long interval = 1000;           // interval at which to blink (milliseconds)

 
int buttonState = 0;
boolean flag = false;
void setup() {
  size(320,240);
  zigBlack = createFont("Ubuntu Mono", fontSize);  
  textFont(zigBlack);
  background(0); // Set background to black
  textSize(45);
  for (int i = 0; i < fifolength; i++) {
        
       words+="0";
     }
     //println(encodeMorseCode("_..."));
}
void keyTyped() {
  // The variable "key" always contains the value 
  // of the most recent key pressed.
  if (key == ' ' || key == '.' || key == '-') {
     switch(key){
       case ' ' :
       fifoBuffer=0;
       break;
       case '.' :
       fifoBuffer=1;
       break;
       case '-' :
       fifoBuffer=2;
       break;
     }
     
     fifififo();
      
   }
   
    
}
void draw() {

  long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    fifififo();
     
  }
  //
   
   
   text(words , 10, 50 , 300, 50);   
  //
   
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
  
    
   
}
String encodeMorseCode(String in_string) {
    
  String TextInput = in_string;
  String MorseCode = new String();
  String[] AlphabetArray = {
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", 
    "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"
  };
  String[] MorseCodeArray = {
    "._", "_...", "_._.", "_..", ".", ".._.", "__.", "....", "..", ".___", "_._", "._..", "__", 
    "_.", "___", ".__.", "__._", "._.", "...", "_", ".._", "..._", ".__", "_.._", "_.__", "__.."
  };
  
   
    for (int j=0; j<MorseCodeArray.length; j++) {
      if (TextInput.equals(MorseCodeArray[j])) {
        MorseCode += AlphabetArray[j] + " " ;
      }
    }
  
  return MorseCode;
}