#include "Device_config.h"
  #define MYDEBUG


void updateSensorValues () {
  readGasPercentage(device.sensor0);
  readGasPercentage(device.sensor1);
  readGasPercentage(device.sensor2);
  readGasPercentage(device.sensor3);
}

void sendToPi(String& s){
  Serial.println(s);
}
void myDebug(String s){
  #ifdef MYDEBUG
  Serial.println(s);
  #endif
}
