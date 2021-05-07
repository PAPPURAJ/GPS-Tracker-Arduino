#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "iotdemo-c0d3f-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "fZgTbsoG2t6tevpagt9HDxf1c4P7pias3Yspsovb"
#define WIFI_SSID "Hidden Network"
#define WIFI_PASSWORD "roboment20188"

#include<SoftwareSerial.h>
#include <TinyGPS++.h>

FirebaseData firebaseData;
FirebaseJson json;

SoftwareSerial myS(0,2);

double Lat=10,Lon=11;
TinyGPSPlus gps;



void writeDB(String field,String value){
 Firebase.setString(firebaseData, "/"+field,value );
  
}







void setup() {
  myS.begin(9600);
  
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  writeDB("Test","Ok");

}

void loop() {
  
   while(myS.available())              //While there are incoming characters  from the GPS
  {
    gps.encode(myS.read());           //This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())          //This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
   
    Lat=gps.location.lat();
    Lon=gps.location.lng();
    Serial.println(Lat,6);
    Serial.println(Lon,6);

    writeDB("Lat",String(Lat,6));
    writeDB("Lon",String(Lon,6));

  }

}
