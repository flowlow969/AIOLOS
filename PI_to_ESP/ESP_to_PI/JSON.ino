#include <ArduinoJson.h>
#include"structs.h"

//String generateJsonMessage(Node* node);

String generateJsonMessage(Node* node) {
  const String NODE = "Node";
  const String SENSORS = "Sensors";
  const String TYPE = "Type";
  const String VALUE = "Value";
 
  DynamicJsonDocument  doc(1024);
  doc[NODE] = node->id;
  JsonArray sensorList = doc.createNestedArray(SENSORS);
  
  JsonObject sensor = sensorList.createNestedObject();
  sensor[TYPE] = node->sensor1.typ;
  sensor[VALUE] = getSensorValue(node->sensor1);
  
  JsonObject sensor2 = sensorList.createNestedObject();
  sensor2[TYPE] = node->sensor2.typ;
  sensor2[VALUE] = getSensorValue(node->sensor2);
  
  JsonObject sensor3 = sensorList.createNestedObject();
  sensor3[TYPE] = node->sensor3.typ;
  sensor3[VALUE] = getSensorValue(node->sensor3);

  String retString;
  serializeJson(doc, retString);
  return retString;
}
