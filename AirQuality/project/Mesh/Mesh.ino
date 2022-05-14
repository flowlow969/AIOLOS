#include <esp_now.h>
#include "painlessMesh.h"
#include <Arduino_JSON.h>


//Zuordnung des Nodes. (Wichtig: hochzählen)
int nodeNumber = 1;

//Pin zuordnung
#define ANALOG_PIN 34
#define HEAT_LED_PIN 32

// MESH Einstellungen
#define   MESH_PREFIX     "AIOLOS" //name vom mesh
#define   MESH_PASSWORD   "MESHpassword" //Passwort vom mesh
#define   MESH_PORT       5555 // port



//Nachicht
String readings;

Scheduler userScheduler; //Schedule
painlessMesh  mesh;

//Funktionsprototypen
void sendMessage() ; //Nachicht Senden
String getReadings(); 
int readGasPercentig();

//Task: Messungen sammeln und senden
Task taskSendMessage(TASK_SECOND * 5 , TASK_FOREVER, &sendMessage);


int readGasPercentig(){
  //Sensor Auslesen
  uint16_t gasVal;
  gasVal = analogRead(ANALOG_PIN);
  //Messwert in den Richtigen Rahmen mappen
  gasVal = map(gasVal, 0, 1023, 0, 100);
  //Messwert Prüfen
 if (isnan(gasVal)) {    
    Serial.println("Fehler beim Auslessen des Sensors");
    return -1;
  }
  else {
    return gasVal;
  }
}

String getReadings () {
  JSONVar jsonReadings;
  jsonReadings["node"] = nodeNumber;
  jsonReadings["gas"] = readGasPercentig();
  readings = JSON.stringify(jsonReadings);
  return readings;
}

void sendMessage () {
  String msg = getReadings();
  mesh.sendBroadcast(msg);
}



// Callback handeler für Painles Mesh Lib
void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
  JSONVar myObject = JSON.parse(msg.c_str());
  int node = myObject["node"];
  int gas = myObject["gas"];
  Serial.print("Node: ");
  Serial.println(node);
  Serial.print("Gas concentraton: ");
  Serial.print(gas);
  Serial.println(" %");
  
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);
  //Sensor Vorheitzen für Stabilere Messwerte
  pinMode(HEAT_LED_PIN, OUTPUT);  
  digitalWrite(HEAT_LED_PIN, HIGH); // LED an
  Serial.println("The sensor is warming up...");
  delay(30000);
  digitalWrite(HEAT_LED_PIN, LOW); //LED aus
  

  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

void loop() {
  mesh.update();
}