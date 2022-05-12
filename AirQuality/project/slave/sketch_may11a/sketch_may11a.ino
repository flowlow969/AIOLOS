#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

#define BOARD_ID 1 // Definieren welches Board es sit


#define ANALOG_PIN 34  // Eingang Gas Sensor

int tst = 0;

uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0x7B, 0xB7, 0xC8};  //Mac Adresse des Masters

typedef struct struct_message {
  int id;
  int gas;
  unsigned int readingId;
} struct_message;   //Datenstruktur

struct_message myData;   //Struktur Intialisieren

//Timing
unsigned long previousMillis = 0; //Zeit der Letzten Übertragung
unsigned long IntigrationTime = 1000; //Periodendauer der Messung

unsigned int readingId = 0; //Messungs Zähler Init

constexpr char WIFI_SSID[] = "Panama"; //WIFI name

int32_t getWiFiChannel(const char *ssid) {
  if (int32_t n = WiFi.scanNetworks()) {
      for (uint8_t i=0; i<n; i++) {
          if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
              return WiFi.channel(i);
          }
      }
  }
  return 0;
}

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

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLatzte Datenübertragung an den Master:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Datenlieferung erfolgreich" : "Datenlieferung fehlgeschlagen");
}

void setup() {
Serial.begin(115200);
Serial.println("The sensor is warming up...");
delay(30000);
WiFi.mode(WIFI_STA);
int32_t channel = getWiFiChannel(WIFI_SSID);

WiFi.printDiag(Serial); // Uncomment to verify channel number before
esp_wifi_set_promiscuous(true);
esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
esp_wifi_set_promiscuous(false);
WiFi.printDiag(Serial); // Uncomment to verify channel change after
//Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  //Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.encrypt = false;
  
  //Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
void loop() {

unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= IntigrationTime) {
    // Save the last time a new reading was published
    previousMillis = currentMillis;
    //Set values to send
    myData.id = BOARD_ID;
   
    myData.gas = readGasPercentig();
    myData.readingId = readingId++;
     
    //Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    if (result == ESP_OK) {
      Serial.println("Messung erflogreich gesendet");
    }
    else {
      Serial.println("Fehler beim senden der Datetn");
    }
  }
}