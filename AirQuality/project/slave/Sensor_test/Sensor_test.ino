#include <esp_now.h>
#define ANALOG_PIN 12 
uint16_t gasVal;
void setup() {
Serial.begin(115200);
Serial.println("The sensor is warming up...");
delay(3000);
}
void loop() {
gasVal = analogRead(ANALOG_PIN);
gasVal = map(gasVal, 0, 1023, 0, 100);
Serial.print("Gas percentage: ");
Serial.print(gasVal);
Serial.print("%\n");
delay(2000);
}