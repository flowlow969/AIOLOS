#include "painlessMesh.h"
//#include "configs/Device_config0.h"
//#include "configs/Device_config1.h"
#include "configs/Device_config2.h"
//#include "configs/Device_config3.h"



#define ANALOG_PIN 34

// MESH Details
#define   MESH_PREFIX     "AIOLOSmesh" //name for your MESH
#define   MESH_PASSWORD   "somethingsneaky" //password for your MESH
#define   MESH_PORT       5555 //default port



Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain

//Create tasks: to send messages and get readings;
Task taskSendMessage(TASK_SECOND * 10 , TASK_FOREVER, &sendMessage);




void sendMessage () {
  updateSensorValues();
  String temp = generateJsonMessage(device);
  sendToPi(temp);
  mesh.sendBroadcast(temp);
}

// Needed for painless library
void receivedCallback( uint32_t from, String &msg ) {
  sendToPi(msg); //send msg to pi
}


void MeshSetup() {
  //mesh.setDebugMsgTypes( ERROR | MESH_STATUS | CONNECTION | SYNC | COMMUNICATION | GENERAL | MSG_TYPES | REMOTE ); // all types on
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}
void MeshUpdate() {
  mesh.update();
}



void newConnectionCallback(uint32_t nodeId) {
// myDebug("New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  myDebug("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  //myDebug("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}
