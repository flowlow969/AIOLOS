#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
  String typ;
  int value;
  int adc;
  int rangeMin; //ppm
  int rangeMax; //ppm
}Sensor;

typedef struct {
  int id;
  Sensor sensor0;
  Sensor sensor1;
  Sensor sensor2;
  Sensor sensor3;
}Node;

const String MQ_NONE = "MQ-NONE";
const String MQ_2 = "MQ-2";
const String MQ_3 = "MQ-3";
const String MQ_4 = "MQ-4";
const String MQ_5 = "MQ-5";
const String MQ_6 = "MQ-6";
const String MQ_7 = "MQ-7";
const String MQ_8 = "MQ-8";
const String MQ_9 = "MQ-9";
const String MQ_135 = "MQ-135";

#endif
