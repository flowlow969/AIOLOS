// Complete Instructions to Get and Change ESP MAC Address: https://RandomNerdTutorials.com/get-change-esp32-esp8266-mac-address-arduino/

#include <WiFi.h>


void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("ESP Board");
  delay(2000);
  Serial.println(WiFi.macAddress());
}
 
void loop(){

}