
#include"structs.h"


Node node;
Sensor s2;
Sensor s1;
Sensor s3;


void setup() {
  Serial.begin(9600);
  Sensor s1;
  s1.typ = MQ_2;
  s1.value = 5000;
  s1.rangeMin = 0;
  s1.rangeMax = 100000;

  Sensor s3;
  s3.typ = MQ_3;
  s3.value = 5000;
  s3.rangeMin = 0;
  s3.rangeMax = 100000;

  Sensor s2;
  s2.typ = MQ_5;
  s2.value = 5000;
  s2.rangeMin = 0;
  s2.rangeMax = 100000;

  node.id = 1;
  node.sensor1 = s1;
  node.sensor2 = s2;
  node.sensor3 = s3;

}

void loop() {
  delay(1000);
  String s = generateJsonMessage(&node);
  Serial.println(s);
}
