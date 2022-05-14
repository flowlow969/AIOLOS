#include <ArduinoJson.h>
#include"structs.h"

//String generateJsonMessage(Node* node);

String generateJsonMessage(Node& node) {
  const String NODE = "Node";
  const String SENSORS = "Sensors";
  const String TYPE = "Type";
  const String VALUE = "Value";

  DynamicJsonDocument  doc(1024);
  doc[NODE] = node.id;
  JsonArray sensorList = doc.createNestedArray(SENSORS);

  JsonObject sensor = sensorList.createNestedObject();
  sensor[TYPE] = node.sensor0.typ;
  sensor[VALUE] = node.sensor0.value;

  JsonObject sensor1 = sensorList.createNestedObject();
  sensor1[TYPE] = node.sensor1.typ;
  sensor1[VALUE] = node.sensor1.value;

  JsonObject sensor2 = sensorList.createNestedObject();
  sensor2[TYPE] = node.sensor2.typ;
  sensor2[VALUE] = node.sensor2.value;

  JsonObject sensor3 = sensorList.createNestedObject();
  sensor3[TYPE] = node.sensor3.typ;
  sensor3[VALUE] = node.sensor3.value;

  String retString;
  serializeJson(doc, retString);
  return retString;
}
