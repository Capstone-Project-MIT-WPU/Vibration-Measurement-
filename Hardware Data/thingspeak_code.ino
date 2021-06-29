#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>;
#include <Wire.h>
#include <Adafruit_ADS1X15.h> 
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
#include <math.h>


Adafruit_ADS1115 ads;
static const int RXPin = 12, TXPin = 13;
static const uint32_t GPSBaud = 9600;

const char * myWriteAPIKey = "3OGJRCHQ6H373XDP";                       //api key from thingspeak
const char* ssid = "Shubhangi singh";                                  //wifi name
const char* password = "shubh123";                                     //wifi password
const char* server = "api.thingspeak.com";
unsigned long myChannelNumber =1291300;                                //channel id from thingspeak

WiFiClient client;
int xpin = A0;                
int xvalue;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


void setup()

{
pinMode(2, OUTPUT); 
pinMode(0, OUTPUT);
Serial.begin(115200);
ss.begin(GPSBaud);

delay(1);

// Connect to WiFi network
ads.begin();
WiFi.begin(ssid, password);

Serial.println();

Serial.println("WiFi connected to shubhangi singh");
Serial.println();
ThingSpeak.begin(client);

}

void loop()
{
   // This sketch displays information every time a new sentence is correctly encoded.
    while(ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
  //------------------------------ADXL_g-----------------------------------------------------------------------------------------------
  int16_t adc0,adc2;
  adc0 = ads.readADC_SingleEnded(0);
  adc2 = ads.readADC_SingleEnded(2);
  xvalue = analogRead(xpin);                               //reads values from x-pin & measures acceleration in X direction 
  int x = map(xvalue, 399, 590, -100, 100);               //maps the extreme ends analog values from -100 to 100 for our understanding
  int y = map(adc0, 6911, 10507, -1000, 1000);
  int z = map(adc2, 6911, 10507, -1000, 1000);
  
  float xg = (float)x/(-100.00);                          //converts the mapped value into acceleration in terms of "g"
  float yg = (float)y/(-1000.00);
  float zg =(float)z/(-1000.00);
  float acc=  sqrt( float(xg*xg)+float(yg*yg)+float(zg*zg));    

  Serial.print(xg); 
  Serial.print("g   ");                                     //prints value of acceleration in X directio                                   //prints "g"
  Serial.print(yg);                                       //prints value of acceleration in X direction
  Serial.print("g   ");                                   //prints "g"
  Serial.print(zg);                                       //prints value of acceleration in X direction
  Serial.print("g   ");                                   //prints "g"
  Serial.print(acc);                                       //prints value of acceleration in X direction
  Serial.print("g   ");                                    //prints "g"
  Serial.print('\t'); 
  Serial.print('\n'); 
                                  
  
  if(acc>=3.2 || acc<=-3.2){ 
    digitalWrite(2, HIGH); //switch green LED on
  }else{
     digitalWrite(2, LOW);
  }
  if(acc>-3.2 && acc<3.2){ 
    digitalWrite(0, HIGH); //switch red LED on
  }else{
     digitalWrite(0, LOW);
  }
  
     
//----------------------THINGSPEAK-----------------------------------------------------------------------------------------------------
 ThingSpeak.setField(1, xg);
 ThingSpeak.setField(2, yg);
 ThingSpeak.setField(5, zg);
 ThingSpeak.setField(6, acc);
 ThingSpeak.writeFields(1291300, myWriteAPIKey);  
}

void displayInfo()
{
 // Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {

    double latitude = (gps.location.lat());
    double longitude = (gps.location.lng());
    
    String latbuf;
    latbuf += (String(latitude, 6));
    //Serial.println(latbuf);

    String lonbuf;
    lonbuf += (String(longitude, 6));
    //Serial.println(lonbuf);

    ThingSpeak.setField(3, latbuf);
    ThingSpeak.setField(4, lonbuf);
    ThingSpeak.writeFields(1291300, myWriteAPIKey);  
    
  }
  else
  {
    //Serial.print(F("INVALID"));
  }

}

