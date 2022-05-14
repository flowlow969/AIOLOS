#include <Wire.h>
#include "structs.h"
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;
const int ACDUPPERBOUND = 16348;
const int ACDLOWERBOUND = 0;

void adcSetup() {
  ads.setGain(GAIN_TWOTHIRDS);// 2/3x +/- 6.144V 1bit = 0.1875mV default
  ads.begin();
}

void readGasPercentage(Sensor &sensor) {
  if (sensor.adc < 0 || sensor.adc > 3) {
    myDebug("ADC ID is out of bound\n");
    sensor.value = -1;
    return;
  }
  //Sensor Auslesen
  uint16_t gasVal, gasValMapped;
  gasVal = ads.readADC_SingleEnded(sensor.adc);
  //Messwert in den Richtigen Rahmen mappen
  gasValMapped = map(gasVal, ACDLOWERBOUND, ACDUPPERBOUND,  sensor.rangeMin, sensor.rangeMax);
  //Messwert Prüfen
  if (isnan(gasVal)) {
    myDebug("Fehler beim Auslessen des Sensors\n");
    sensor.value = -1;
  }
  else {
    sensor.value = gasVal;
  }
}

void updateSensorValues () {
  readGasPercentage(device.sensor0);
  readGasPercentage(device.sensor1);
  readGasPercentage(device.sensor2);
  readGasPercentage(device.sensor3);
}
