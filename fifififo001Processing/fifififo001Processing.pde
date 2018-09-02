//19 47 14  // vi tester med 30

// fifo kan være 0 eller 1
int fifo[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
PFont zigBlack;
char letter;
// String words = "---...";
String words = "";
String[] myArray = new String[16];
 
int fontSize = 50;
int screenWidth = 800;//displayWidth-fontSize;
int screenHeight= 600;//displayHeight-fontSize;
// tryk på escape knappen for at kom ud af fullscreen

int startTime = 0;
int timeout = 60000; // hvor længe skal vi vente før vi nulstiller pt et minut

void setup() {
  // size(400, 800);
  fullScreen(); // use this later
  screenWidth = displayWidth-2*fontSize;
  screenHeight= displayHeight-2*fontSize;
    
  // Create the font
     
  // zigBlack = createFont("Chunkfive Ex", fontSize);
  zigBlack = createFont("Ubuntu Mono", fontSize);  
  textFont(zigBlack);
  //fill(0);
  for(int y = 0; y<myArray.length; y++){
   myArray[y]=" ";
  } 
  startTime=millis();
}

void draw() {
   background(0); // Set background to black
   textSize(50);
   for(int y = 0; y<myArray.length; y++){
   text(myArray[y] , 50, 50+(y*50), screenWidth, 55);   
  } 
  
  if(millis() > (startTime+timeout)){ // fuuuck det virker ikke ?
    resetAll();
  }
}
void resetAll(){
  for(int y = 0; y<myArray.length; y++){
   myArray[y]=" ";
  } 
  startTime=millis();
}
void keyTyped() {
  // The variable "key" always contains the value 
  // of the most recent key pressed.
  if ((key >= 'A' && key <= 'z') || key == ' ' || key == '.' || key == '-') {
    letter = key;
     
    }
    
}