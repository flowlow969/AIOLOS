#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#include "structs.h"

Sensor s0 = {
  .typ = MQ_NONE,
  .value = 0,
  .adc = 0,
  .rangeMin = 0,
  .rangeMax = 0
};
Sensor s1 = {
  .typ = MQ_NONE,
  .value = 0,
  .adc = 0,
  .rangeMin = 0,
  .rangeMax = 0
};
Sensor s2 = {
  .typ = MQ_NONE,
  .value = 0,
  .adc = 0,
  .rangeMin = 0,
  .rangeMax = 0
};
Sensor s3 = {
  .typ = MQ_NONE,
  .value = 0,
  .adc = 0,
  .rangeMin = 0,
  .rangeMax = 0
};
Node device = {
  .id = 2,
  .sensor0 = s0,
  .sensor1 = s1,
  .sensor2 = s2,
  .sensor3 = s3
};

#endif
