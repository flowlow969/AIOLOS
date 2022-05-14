#include <structs.h>

#define DEBUG

#ifdef DEBUG
  
#endif



void setup() {
  Serial.begin(115200);
  
  delay(30000); //warming up the sensores
  #ifdef DEBUG
  Serial.println("The sensores is warming up...");
  #endif


void loop() {
  mesh.update();
}
