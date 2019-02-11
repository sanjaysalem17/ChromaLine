#include <Adafruit_TCS34725.h>
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
#include <QTRSensors.h>
QTRSensorsAnalog qtra((unsigned char[]) {A3, A4, A5}, 3, 4, QTR_NO_EMITTER_PIN);
unsigned int sensors[3];
int value1 = 0;
int value2 = 0;
int value3 = 0;
int count = 0;
int prevval = 0;
long ONE = 1;
long ZERO = 0;
#include <AFMotor.h>
AF_DCMotor r(1, MOTOR12_2KHZ);
AF_DCMotor l(2, MOTOR12_2KHZ);
int pingPin = A1; // Trigger Pin of Ultrasonic Sensor
int echoPin = A2; // Echo Pin of Ultrasonic Sensor
#include <LiquidCrystal.h>
LiquidCrystal lcd(32, 33, 34, 35, 36, 37);
void setup() {
  Serial.begin(9600);
  r.setSpeed(400);
  l.setSpeed(400);
  tcs.begin();
  lcd.begin(16, 2);
  lcd.setCursor(5, 0);
  lcd.print("HELLO!");
  
}
void loop() {  
  r.run(FORWARD);
  l.run(FORWARD);
  delay(1000);
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
  uint16_t clearr, red, green, blue;
  tcs.getRawData(&red, &green, &blue, &clearr);
  delay(60);  // takes 50ms to read 
  uint32_t sum = clearr;
  float R, G, B;
  R = red; R /= sum; //R /= 256;
  G = green; G /= sum; //G /= 256;
  B = blue; B /= sum; //B /= 256;
  if(R >= .4 or G >= .35 or B >= .35){
    lcd.clear();
  if(R >= .4){
    if(B >= .35){
      lcd.print("PURPLE");
      r.run(RELEASE);
      l.run(FORWARD);
      //songName(lcd, "JINGLE", "BELLS");
      //playSong(jingle, beatsjingle, jingleTemp, 12);
    }
    else if(G >= .35){
      lcd.print("YELLOW-ORANGE");
      l.run(RELEASE);
      //songName(lcd, "SLEIGH", "RIDE");
      //playSong(sleigh, beatssleigh, sleighTemp, 15);
    }
    else{
      lcd.print("RED");
      r.run(RELEASE);
      l.run(BACKWARD);
      
      //songName(lcd, "CAROL", "OF THE BELLS");
      //playSong(carol, beatscarol, carolTemp, 17);      
    }
  }
  else if(B >= .35){
    if(G >= .35){
      lcd.print("BLUE-GREEN");
      l.run(RELEASE);
      r.run(BACKWARD);
      
      //songName(lcd, "DECK THE", "HALLS");
      //playSong(deck, beatsdeck, deckTemp, 18);
    }
    else{
      
      lcd.print("BLUE");
      r.run(BACKWARD);
      l.run(BACKWARD);
      r.run(RELEASE);
      l.run(RELEASE);
      r.run(FORWARD);
      l.run(FORWARD);
      r.run(RELEASE);
      l.run(RELEASE);
      
      //songName(lcd, "MERRY", "CHRISTMAS");
      //playSong(wish, beatswish, wishTemp, 31);
      
    }
  }
  else {
    lcd.print("GREEN");
    r.run(FORWARD);
    l.run(FORWARD);
    r.run(RELEASE);
    l.run(RELEASE);
    r.run(BACKWARD);
    l.run(BACKWARD);
    r.run(RELEASE);
    l.run(RELEASE);
    //songName(lcd, "ON THE LAST", "DAY OF FINALS");
    //playSong(days, beatsdays, daysTemp, 22);
    
  }
    
  }
  if(inches <= 10) {
    Serial.println("TOO CLOSE!");
    if (random() == ZERO){
      if(random() == ZERO){
        l.run(RELEASE);
      }
      else {
        r.run(RELEASE);
      }
      
    }
    else {
      if(random() == ONE){
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
  
  delay(20);
  //infrared();
  r.run(FORWARD);
  l.run(FORWARD); 
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
long printRand() {
   return random(4); 
   
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

void backNForth(){
  for(int i = 0; i < 1; i++){
    r.run(BACKWARD);
    l.run(BACKWARD);
    r.run(RELEASE);
    l.run(RELEASE);
    r.run(FORWARD);
    l.run(FORWARD);
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
    l.run(BACKWARD);
    r.run(RELEASE);
    l.run(RELEASE);
  } 
}

void uSonic(){
  if (printRand() == ZERO){
      l.run(RELEASE);
    }
    else if (printRand() == 1){
      r.run(RELEASE);
    }
    else if (printRand() == 2){
      r.run(RELEASE);
      l.run(RELEASE);
      r.run(BACKWARD);
      l.run(BACKWARD);
      r.run(RELEASE);
      
    }
    else {
      r.run(RELEASE);
      l.run(RELEASE);
      r.run(BACKWARD);
      l.run(BACKWARD);
      l.run(RELEASE);
    }
}
/*void infrared(){
  qtra.read(sensors);
  value1 = sensors[0];
  value2 = sensors[1];
  value3 = sensors[2];
  prevval= max1(value1, value2, value3);
  if((value1 ==0 || value2==0 || value3==0) && prevval==1){ // something is detected
    count++;
    if (random() == ZERO){
      if(random() == ZERO){
        l.run(RELEASE);
      }
      else {
        r.run(RELEASE);
      }
    }
    else {
      if(random() == ONE){
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
}*/
void colorRead(float R, float G, float B){
  lcd.clear();
  if(B >= .35){
    if(R >= .4){
      lcd.print("PURPLE");
      r.run(RELEASE);
      
      //songName(lcd, "JINGLE", "BELLS");
      //playSong(jingle, beatsjingle, jingleTemp, 12);
    }
    else if(G >= .35){
      lcd.print("BLUE-GREEN");
      l.run(RELEASE);
      //songName(lcd, "SLEIGH", "RIDE");
      //playSong(sleigh, beatssleigh, sleighTemp, 15);
    }
    else{
      lcd.print("BLUE");
      r.run(RELEASE);
      l.run(BACKWARD);
      
      //songName(lcd, "CAROL", "OF THE BELLS");
      //playSong(carol, beatscarol, carolTemp, 17);      
    }
  }
  else if(G >= .35){
    if(R >= .4){
      lcd.print("YELLOW-ORANGE");
      l.run(RELEASE);
      r.run(BACKWARD);
      
      //songName(lcd, "DECK THE", "HALLS");
      //playSong(deck, beatsdeck, deckTemp, 18);
    }
    else{
      
      lcd.print("GREEN");
      backNForth();
      
      //songName(lcd, "MERRY", "CHRISTMAS");
      //playSong(wish, beatswish, wishTemp, 31);
      
    }
  }
  else {
    lcd.print("RED");
    forthNBack();
    //songName(lcd, "ON THE LAST", "DAY OF FINALS");
    //playSong(days, beatsdays, daysTemp, 22);
    
  }
}
