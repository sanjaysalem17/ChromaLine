
#include <Wire.h>
#include <Adafruit_TCS34725.h>

#include <LiquidCrystal.h>
LiquidCrystal lcd(32, 33, 34, 35, 36, 37);

byte music[] = {0x03,0x0D,0x09,0x09,0x09,0x0B,0x1B,0x18};
// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
//#define redpin 3
//#define greenpin 5
//#define bluepin 6
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
//#define commonAnode true

// our RGB -> eye-recognized gamma color
//byte gammatable[256];
byte music1[] = {0x00,0x00,0x00,0x10,0x18,0x1C,0x16,0x12};
byte music2[] = {0x00,0x03,0x07,0x07,0x03,0x00,0x00,0x00};
byte music3[] = {0x12,0x10,0x10,0x10,0x00,0x00,0x00,0x00};


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
char jingle[] = {'b', 'b', 'b', 'b', 'b', 'b', 'b', 'D', 'g', 'a', 'b', ' '};
int beatsjingle[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 3, 1};
int jingleTemp = 253;
char sleigh[] = {'D', 'D', 'D', 'D', 'E', 'D', 'b', 'g', 'a', 'b', 'a', 'F', 'e', 'g', ' '};
int beatssleigh[] = {2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 1, 1, 2, 8, 1};
int sleighTemp = 208;
char carol[] = {'g', 'F', 'g', 'e', 'g', 'F', 'g', 'e', 'g', 'F', 'g', 'e', 'g', 'F', 'g', 'e', ' '};
int beatscarol[] = {2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 1};
int carolTemp = 250;
char deck[] = {'C', 'A', 'a', 'g', 'f', 'g', 'a', 'f', 'g', 'a', 'A', 'g', 'a', 'g', 'f', 'e', 'f', ' '};
int beatsdeck[] = {3, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 3, 1, 2, 2, 4, 1};
int deckTemp = 236;
char wish[] = {'d', 'g', 'g', 'a', 'g', 'F', 'e', 'e', 'e', 'a', 'a', 'b', 'a', 'g', 'F', 'd', 'd', 'b', 'b', 'C', 'b', 'a', 'g', 'e', 'd', 'd', 'e', 'a', 'F', 'g', ' '};
int beatswish[] = {2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 2, 2, 2, 4, 1};
int wishTemp = 300;
char days[] = {'d', 'd', 'd', 'g', 'g', 'g', 'F', 'g', 'a', 'b', 'C', 'a', 'b', 'C', 'D', 'E', 'C', 'b', 'g', 'a', 'g', ' '};
int beatsdays[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 2, 6, 1};
int daysTemp = 224;
int buzzerPin = A0;
void setup() {
  Serial.begin(9600);
  lcd.createChar(1, music1);
  lcd.createChar(2, music2);
  lcd.createChar(3, music3);
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT);
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  
  // use these three pins to drive an LED
  //pinMode(redpin, OUTPUT);
  //pinMode(greenpin, OUTPUT);
  //pinMode(bluepin, OUTPUT);
  
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see

}


void loop() {
  uint16_t clearr, red, green, blue;

  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clearr);

  tcs.setInterrupt(true);  // turn off LED
  
  Serial.print("C:\t"); Serial.print(clearr);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);

  // Figure out some basic hex code for visualization
  uint32_t sum = clearr;
  float R, G, B;
  R = red; R /= sum; R /= 256;
  G = green; G /= sum; G /= 256;
  B = blue; B /= sum; B/= 256;
  lcd.clear();
  if(R >= 230){
    if(B >= 230){
      songName("JINGLE", "BELLS");
      //playSong(jingle, beatsjingle, jingleTemp);
    }
    else if(G >= 230){
      songName("SLEIGH", "RIDE");
      //playSong(sleigh, beatssleigh, sleighTemp);
    }
    else{
      songName("CAROL", "OF THE BELLS");
      //playSong(carol, beatscarol, carolTemp);      
    }
  }
  else if(G >= 230){
    if(B >= 230){
      songName("DECK THE", "HALLS");
      //playSong(deck, beatsdeck, deckTemp);
    }
    else{
      
      songName("MERRY", "CHRISTMAS");
      //playSong(wish, beatswish, wishTemp);
      
    }
  }
  else {
    songName("ON THE LAST", "DAY OF FINALS");
    //playSong(days, beatsdays, daysTemp);
    
  }
  delay(2000);

  //Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );

 
}
void playSong(char notes[], int beats[], int tempo) {
  int songLength = sizeof(notes)/sizeof(int);
  int i, duration;

  for (i = 0; i < songLength; i++) {
    duration = beats[i] * tempo;

    if (notes[i] == ' '){
      delay(duration);            
    }
    else {
      tone(buzzerPin, frequency(notes[i]), duration);
      delay(duration);            
    }
    delay(tempo/10);              
  } 
}
int frequency(char note) { 
  int i;
  const int numNotes = 12;  
  char names[] = { 'c', 'd', 'e', 'f', 'F', 'g','a', 'A', 'b', 'C', 'D', 'E'};
  int frequencies[] = {262, 294, 330, 349, 370, 392, 440, 466, 494, 523, 587, 659};
  for (i = 0; i < numNotes; i++)
  {
    if (names[i] == note)         
    {
      return(frequencies[i]);     
    }
  }
  return(0);  
}
void songName(String name1, String name2){
  lcd.setCursor(1, 0);
  lcd.write(byte(1));
  lcd.setCursor(15, 0);
  lcd.write(byte(1));
  lcd.setCursor(0, 1);
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.setCursor(14, 1);
  lcd.write(byte(2));
  lcd.write(byte(3));
  int start1 = (16 - name1.length())/2;
  lcd.setCursor(start1, 0);
  lcd.print(name1);
  int start2 = (16 - name2.length())/2;
  lcd.setCursor(start2, 1);
  lcd.print(name2);
  
}
