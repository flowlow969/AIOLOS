#include <Wire.h>
#include "structs.h"
#include <Adafruit_ADS1X15.h>
#define MYDEBUG

Adafruit_ADS1115 ads;

void adcSetup(){
  ads.setGain(GAIN_TWOTHIRDS);// 2/3x +/- 6.144V 1bit = 0.1875mV default
  ads.begin();
}

  void readGasPercentage(Sensor &sensor){
    if(sensor.adc >=0 && sensor.adc <= 3){
    //Sensor Auslesen
    uint16_t gasVal;
    gasVal = ads.readADC_SingleEnded(sensor.adc);
     #ifdef MYDEBUG
    Serial.print(sensor.typ);
    Serial.print(" \n");
    Serial.print(sensor.adc);
    Serial.print(" \n");
    Serial.print(gasVal);
    Serial.println(" %");
    #endif MYDEBUG
    //Messwert in den Richtigen Rahmen mappen
    gasVal = map(gasVal, 0, 16348,  sensor.rangeMin, sensor.rangeMax);
    #ifdef MYDEBUG
    Serial.print(sensor.typ);
    Serial.print(" \n");
    Serial.print(sensor.adc);
    Serial.print(" \n");
    Serial.print(gasVal);
    Serial.println(" %");
    #endif MYDEBUG
    //Messwert Prüfen
   if (isnan(gasVal)) {
      #ifdef MYDEBUG
      Serial.println("Fehler beim Auslessen des Sensors");
      #endif MYDEBUG
      sensor.value = -1;
    }
    else {
      #ifdef MYDEBUG
      Serial.print("ADC: ");
      Serial.println(sensor.adc);
      Serial.print("Gas concentraton: ");
      Serial.print(gasVal);
      Serial.println(" %");
      #endif MYDEBUG
      sensor.value = gasVal;
    }
  }
  else{
      #ifdef MYDEBUG
      Serial.print("ADC ID is out of bound");
      #endif MYDEBUG
    sensor.value = -1;
  }
  }
