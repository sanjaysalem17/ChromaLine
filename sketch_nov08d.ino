
#include <Adafruit_TCS34725.h>
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
#include <QTRSensors.h>
QTRSensorsAnalog qtra((unsigned char[]) {A3, A4, A5}, 3, 4, QTR_NO_EMITTER_PIN);
unsigned int sensors[3];
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
int sensor1 = A3;
int sensor2 = A4;
int sensor3 = A5;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int count = 0;
int prevval = 0;
const long ONE = 1;
const long ZERO = 0;
#include <AFMotor.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(32, 33, 34, 35, 36, 37);
byte music1[] = {0x00,0x00,0x00,0x10,0x18,0x1C,0x16,0x12};
byte music2[] = {0x00,0x03,0x07,0x07,0x03,0x00,0x00,0x00};
byte music3[] = {0x12,0x10,0x10,0x10,0x00,0x00,0x00,0x00};
AF_DCMotor r(1, MOTOR12_2KHZ);
AF_DCMotor l(2, MOTOR12_2KHZ);
int pingPin = A1; // Trigger Pin of Ultrasonic Sensor
int echoPin = A2; // Echo Pin of Ultrasonic Sensor
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
  tcs.begin();
  lcd.begin(16, 2);
  lcd.createChar(1, music1);
  lcd.createChar(2, music2);
  lcd.createChar(3, music3);
  lcd.setCursor(5, 0);
  lcd.print("Hello!");
  pinMode(buzzerPin, OUTPUT);
  pinMode(sensor1,INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  r.setSpeed(200);
  l.setSpeed(200);
  
}
void loop() {  
  r.run(FORWARD);
  l.run(FORWARD);
  uint16_t clearr, red, green, blue;
  tcs.getRawData(&red, &green, &blue, &clearr);
  delay(60);  // takes 50ms to read 
  uint32_t sum = clearr;
  float R, G, B;
  R = red; R /= sum; R /= 256;
  G = green; G /= sum; G /= 256;
  B = blue; B /= sum; B /= 256;
  if(R >= 230 or G >= 230 or B >= 230){
    colorRead(R, G, B);
  }
  delay(2000);
  lcd.clear();
  
  long duration, inches, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = microsecondsToInches(duration);
  if(inches <= 15) {
    uSonic();
  }
  delay(1000);
  infrared();
  
  
  r.run(FORWARD);
  l.run(FORWARD); 
  delay(1000);
}

int max1(int a, int b, int c) {
  if(a > b && a > c){
    return a;
  }
  else if(b > a && b > c){
    return b;
  }
  else {
    return c;
  }
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
void playSong(char notes[], int beats[], int tempo, int songLength) {

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
void songName(LiquidCrystal lcd, String name1, String name2){
  lcd.setCursor(1, 0);
  lcd.write(byte(1));
  lcd.setCursor(15, 0);
  lcd.write(byte(1));
  lcd.setCursor(0, 1);
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.setCursor(15, 1);
  lcd.write(byte(2));
  lcd.write(byte(3));
  int start1 = (16 - name1.length())/2;
  lcd.setCursor(start1, 0);
  lcd.print(name1);
  int start2 = (16 - name2.length())/2;
  lcd.setCursor(start2, 1);
  lcd.print(name2);
}
void backNForth(){
  for(int i = 0; i < 1; i++){
    r.run(BACKWARD);
    l.run(BACKWARD);
    r.run(RELEASE);
    l.run(RELEASE);
    r.run(FORWARD);
    r.run(RELEASE);
    l.run(RELEASE);
  } 
}
void forthNBack(){
  for(int i = 0; i < 1; i++){
    r.run(FORWARD);
    l.run(FORWARD);
    r.run(RELEASE);
    l.run(RELEASE);
    r.run(BACKWARD);
    r.run(RELEASE);
    l.run(RELEASE);
  } 
}
void colorRead(float R, float G, float B){
  lcd.clear();
  if(R >= 230){
    if(B >= 230){
    
      r.run(RELEASE);
      songName(lcd, "JINGLE", "BELLS");
      playSong(jingle, beatsjingle, jingleTemp, 12);
    }
    else if(G >= 230){
      l.run(RELEASE);
      songName(lcd, "SLEIGH", "RIDE");
      playSong(sleigh, beatssleigh, sleighTemp, 15);
    }
    else{
      r.run(RELEASE);
      l.run(BACKWARD);
      songName(lcd, "CAROL", "OF THE BELLS");
      playSong(carol, beatscarol, carolTemp, 17);      
    }
  }
  else if(G >= 230){
    if(B >= 230){
      l.run(RELEASE);
      r.run(BACKWARD);
      songName(lcd, "DECK THE", "HALLS");
      playSong(deck, beatsdeck, deckTemp, 18);
    }
    else{
      backNForth();
      songName(lcd, "MERRY", "CHRISTMAS");
      playSong(wish, beatswish, wishTemp, 31);
      
    }
  }
  else {
    forthNBack();
    songName(lcd, "ON THE LAST", "DAY OF FINALS");
    playSong(days, beatsdays, daysTemp, 22);
    
  }
}
void uSonic(){
  if (random(2) == ZERO){
    if(random(2) == ZERO){
      l.run(RELEASE);
     }
    else {
      r.run(RELEASE);
    }
  }
  else {
    if(random(2) == ONE){
      r.run(RELEASE);
      l.run(RELEASE);
      r.run(BACKWARD);
      l.run(BACKWARD);
      delay(1000);
      r.run(RELEASE);
    }
    else {
      r.run(RELEASE);
      l.run(RELEASE);
      r.run(BACKWARD);
      l.run(BACKWARD);
      delay(1000);
      l.run(RELEASE);
      }
    }
}
void infrared(){
  qtra.read(sensors);
  value1 = sensors[0];
  value2 = sensors[1];
  value3 = sensors[2];
  prevval= max1(value1, value2, value3);
  if((value1 ==0 || value2==0 || value3==0) && prevval==1){ // something is detected
    count++;
    if (random(2) == ZERO){
      if(random(2) == ZERO){
        l.run(RELEASE);
      }
      else {
        r.run(RELEASE);
      }
    }
    else {
      if(random(2) == ONE){
        r.run(RELEASE);
        l.run(RELEASE);
        r.run(BACKWARD);
        l.run(BACKWARD);
        delay(1000);
        r.run(RELEASE);
      }
      else {
        r.run(RELEASE);
        l.run(RELEASE);
        r.run(BACKWARD);
        l.run(BACKWARD);
        delay(1000);
        l.run(RELEASE);
      }
    }
  }
}
