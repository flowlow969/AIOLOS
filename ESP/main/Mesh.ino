#include "painlessMesh.h"
#include "Device_config.h"

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
Task taskSendMessage(TASK_SECOND * 5 , TASK_FOREVER, &sendMessage);




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
  mesh.setDebugMsgTypes( ERROR | STARTUP );  // set before init() so that you can see startup messages

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}
void MeshUpdate(){
    mesh.update();
}



void newConnectionCallback(uint32_t nodeId) {
#ifdef DEBUG
  myDebug("New Connection, nodeId = %u\n", nodeId);
#endif
}

void changedConnectionCallback() {
#ifdef DEBUG
  myDebug("Changed connections\n");
#endif
}

void nodeTimeAdjustedCallback(int32_t offset) {
#ifdef DEBUG
  myDebug("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
#endif
}
