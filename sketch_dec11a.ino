#include <LiquidCrystal.h>
LiquidCrystal lcd(32, 33, 34, 35, 36, 37);
#include <Adafruit_TCS34725.h>
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
void setup() {
  // put your setup code here, to run once:
  tcs.begin();
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(5, 0);
  lcd.print("HELLO!");

}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t clearr, red, green, blue;
  tcs.getRawData(&red, &green, &blue, &clearr);
  delay(60);  // takes 50ms to read 
  uint32_t sum = clearr;
  float R, G, B;
  R = red; R /= sum; //R /= 256;
  G = green; G /= sum; //G /= 256;
  B = blue; B /= sum; //B /= 256;
  Serial.print("red: ");
  Serial.print(R);
  Serial.print(" blue: ");
  Serial.print(B);
  Serial.print(" green: ");
  Serial.println(G);
  if(R >= .4 or B >= .35 or G >= .35){
    lcd.clear();
  if(B >= .35){
    if(R >= .4){
      lcd.print("PURPLE");
      //r.run(RELEASE);
      
      //songName(lcd, "JINGLE", "BELLS");
      //playSong(jingle, beatsjingle, jingleTemp, 12);
    }
    else if(G >= .35){
      lcd.print("BLUE-GREEN");
      //l.run(RELEASE);
      //songName(lcd, "SLEIGH", "RIDE");
      //playSong(sleigh, beatssleigh, sleighTemp, 15);
    }
    else{
      lcd.print("BLUE");
      //r.run(RELEASE);
      //l.run(BACKWARD);
      
      //songName(lcd, "CAROL", "OF THE BELLS");
      //playSong(carol, beatscarol, carolTemp, 17);      
    }
  }
  else if(G >= .35){
    if(R >= .4){
      lcd.print("YELLOW-ORANGE");
      //l.run(RELEASE);
      //r.run(BACKWARD);
      
      //songName(lcd, "DECK THE", "HALLS");
      //playSong(deck, beatsdeck, deckTemp, 18);
    }
    else{
      //backNForth();
      lcd.print("GREEN");
      //songName(lcd, "MERRY", "CHRISTMAS");
      //playSong(wish, beatswish, wishTemp, 31);
      
    }
  }
  else {
    lcd.print("RED");
    //forthNBack();
    //songName(lcd, "ON THE LAST", "DAY OF FINALS");
    //playSong(days, beatsdays, daysTemp, 22);
    
  }
  }

}
