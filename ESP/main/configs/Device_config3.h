#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#include "../structs.h"

Sensor s0 = {
  .typ = MQ_135,
  .value = 0,
  .adc = 0,
  .rangeMin = 10,
  .rangeMax = 1000
};
Sensor s1 = {
  .typ = MQ_9,
  .value = 0,
  .adc = 1,
  .rangeMin = 100,
  .rangeMax = 10000
};
Sensor s2 = {
  .typ = MQ_2,
  .value = 0,
  .adc = 2,
  .rangeMin = 300,
  .rangeMax = 10000
};
Sensor s3 = {
  .typ = MQ_NONE,
  .value = 0,
  .adc = -1,
  .rangeMin = 0,
  .rangeMax = 0
};
Node device = {
  .id = 3,
  .sensor0 = s0,
  .sensor1 = s1,
  .sensor2 = s2,
  .sensor3 = s3
};

#endif
