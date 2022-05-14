#include "structs.h"
#include "Device_config.h"

void setup() {
  Serial.begin(115200);
  
  myDebug("The sensores is warming up...");
  delay(30000); //warming up the sensores
  myDebug("done");
  MeshSetup();
}
void loop() {
  MeshUpdate();
}
