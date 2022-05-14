#include <esp_now.h>
#include "painlessMesh.h"
#include <Arduino_JSON.h>

#define ANALOG_PIN 34

// MESH Details
#define   MESH_PREFIX     "RNTMESH" //name for your MESH
#define   MESH_PASSWORD   "MESHpassword" //password for your MESH
#define   MESH_PORT       5555 //default port


//Number for this node
int nodeNumber = 2;

//String to send to other nodes with sensor readings
String readings;

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain
String getReadings(); // Prototype for sending sensor readings

//Create tasks: to send messages and get readings;
Task taskSendMessage(TASK_SECOND * 5 , TASK_FOREVER, &sendMessage);

int readGasPercentig(){
  //Sensor Auslesen
  uint16_t gasVal;
  gasVal = analogRead(ANALOG_PIN);
  //Messwert in den Richtigen Rahmen mappen
  gasVal = map(gasVal, 0, 1023, 0, 100);
  Serial.print("Gas percentage: ");
  Serial.print(gasVal);
  Serial.print("%\n"); 
  //Messwert Prüfen
 if (isnan(gasVal)) {    
    Serial.println("Fehler beim Auslessen des Sonsors");
    return 0;
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



// Needed for painless library
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
  Serial.println("The sensor is warming up...");
  delay(30000);

  

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
  // it will run the user scheduler as well
  mesh.update();
}