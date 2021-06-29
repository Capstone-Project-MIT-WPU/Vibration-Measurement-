#include <Adafruit_ADS1X15.h>
#include <Wire.h> 
Adafruit_ADS1115 ads;

int xpin = A0;

void setup() {
  Serial.begin(9600);
  ads.begin();
}
void loop() {
  int16_t adc0,adc2;
  adc0 = ads.readADC_SingleEnded(0);
  adc2 = ads.readADC_SingleEnded(2);
  int xvalue = analogRead(xpin);                               //reads values from x-pin & measures acceleration in X direction 
  int x = map(xvalue, 399, 590, -100, 100);               //maps the extreme ends analog values from -100 to 100 for our understanding
  int y = map(adc0, 6911, 10507, -1000, 1000);
  int z = map(adc2, 6911, 10507, -1000, 1000);
  
  float xg = (float)x/(-100.00);                          //converts the mapped value into acceleration in terms of "g"
  float yg = (float)y/(-1000.00);
  float zg =(float)z/(-1000.00);
  float acc=  sqrt( float(xg*xg)+float(yg*yg)+float(zg*zg));    
  
//-------------------------------------telemetry-----------------------------------------------------------------------------------
 char xg_text[30];
 char yg_text[30];
 char zg_text[30];
 char acc_text[30];

  dtostrf(xg, 10, 10, xg_text);
  dtostrf(yg, 10, 10, yg_text);
  dtostrf(zg, 10, 10, zg_text);
  dtostrf(acc, 10, 10, acc_text);

  char text[125];
  snprintf(text, 125, "%s,%s,%s,%s", xg_text, yg_text, zg_text, acc_text);
  Serial.println(text); 
//----------------------------------------------------------------------------------------------------------------------------------//

  if(acc>=1.30 || acc<=-1.30){ 
    digitalWrite(2, HIGH); //switch green LED on
  }else{
     digitalWrite(2, LOW);
  }
  if(acc>-1.30 && acc<1.30){ 
    digitalWrite(0, HIGH); //switch red LED on
  }else{
     digitalWrite(0, LOW);
  }
  delay(1);
}

