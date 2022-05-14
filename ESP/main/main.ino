#include "structs.h"

//#define MYDEBUG

void setup() {
  Serial.begin(115200);
  
  myDebug("The sensores is warming up...");
  //delay(30000); //warming up the sensores
  myDebug("done");
  adcSetup();
  MeshSetup();
}
void loop() {
  MeshUpdate();
}
