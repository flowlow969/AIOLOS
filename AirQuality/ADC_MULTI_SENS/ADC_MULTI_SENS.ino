#include <Wire.h>
#include "myStruct.h"
#include <Adafruit_ADS1X15.h>
//#define DEBUG
Adafruit_ADS1115 ads;
int adc0 = 0;



Sensor sensor_a {
  MQ_4,
  0,
  0,
  10000
};
Sensor sensor_b = {
  MQ_5,
  1,
  0,
  10000
};

Node test {
  1,
  sensor_a,
  sensor_b
};


void readGasPercentig(Sensor &sensor){
  if(sensor.adc >=0 && sensor.adc <= 3){
  //Sensor Auslesen
  uint16_t gasVal;
  gasVal = ads.readADC_SingleEnded(sensor.adc);
   #ifdef DEBUG
  Serial.print(sensor.typ);
  Serial.print(" \n");
  Serial.print(sensor.adc);
  Serial.print(" \n");
  Serial.print(gasVal);
  Serial.println(" %");
  #endif DEBUG
  //Messwert in den Richtigen Rahmen mappen
  gasVal = map(gasVal, 0, 16348,  sensor.rangeMin, sensor.rangeMax);
  #ifdef DEBUG
  Serial.print(sensor.typ);
  Serial.print(" \n");
  Serial.print(sensor.adc);
  Serial.print(" \n");
  Serial.print(gasVal);
  Serial.println(" %");
  #endif DEBUG
  //Messwert Prüfen
 if (isnan(gasVal)) {    
    #ifdef DEBUG
    Serial.println("Fehler beim Auslessen des Sensors");
    #endif DEBUG
    sensor.value = -1;
  }
  else {
    #ifdef DEBUG
    Serial.print("ADC: ");
    Serial.println(sensor.adc);
    Serial.print("Gas concentraton: ");
    Serial.print(gasVal);
    Serial.println(" %");
    #endif DEBUG
    sensor.value = gasVal;
  }
}
else{
    #ifdef DEBUG
    Serial.print("ADC ID is out of bound");
    #endif DEBUG
  sensor.value = -1;
}
}

void setup() {
Serial.begin(115200);
ads.setGain(GAIN_TWOTHIRDS);// 2/3x +/- 6.144V 1bit = 0.1875mV default

  ads.begin();
}
void loop() {
readGasPercentig(test.sensor1);

Serial.print("Analog input pin 0: ");
Serial.print(test.sensor1.value);
Serial.print(" ppm \n");
delay(5000);
readGasPercentig(test.sensor2);
Serial.print("Analog input pin 1: ");
Serial.print(test.sensor2.value);
Serial.print(" ppm \n");
delay(5000);
}