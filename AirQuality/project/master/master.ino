#include <esp_now.h>
#include <WiFi.h>
#include <Arduino_JSON.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "draegerguest";
const char* pw = "bird-controller";

typedef struct struct_message {
  int id;
  int gas;
  unsigned int readingId;
} struct_message;

struct_message incomingReadings;

JSONVar board;

AsyncWebServer server(80);
AsyncEventSource events("/events");

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) { 
  // Copies the sender mac address to a string
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  
  board["id"] = incomingReadings.id;
  board["g"] = incomingReadings.gas;
  board["readingId"] = String(incomingReadings.readingId);
  String jsonString = JSON.stringify(board);
  events.send(jsonString.c_str(), "new_readings", millis());
  
  Serial.printf("Board ID %u: %u bytes\n", incomingReadings.id, len);
  Serial.printf("g value: %d \n", incomingReadings.gas);
  Serial.printf("readingID value: %d \n", incomingReadings.readingId);
  Serial.println();
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>Dr&aumlger Gas Sensor DASHBOARD</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p {  font-size: 1.2rem;}
    body {  margin: 0;}
    .topnav { overflow: hidden; background-color: #090088; color: white; font-size: 1.7rem; }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(256,256,256,.5); }
    .cards { max-width: 700px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }
    .reading { font-size: 2.8rem; }
    .packet { color: #bebebe; }
    .card.gas { color: #fd7e14; }
  </style>
</head>
<body>
  <div class="topnav">
    <h3>Dr&aumlger Gas Sensor DASHBOARD</h3>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card gas">
        <h4><i class="gas"></i> BOARD #1 - Gas Concentration</h4><p><span class="reading"><span id="g1"></span> &percnt;</span></p><p class="packet">Reading ID: <span id="rg1"></span></p>
      </div>
    </div>
  </div>
<script>
 
if (!!window.EventSource) {
 var source = new EventSource('/events');
 
 source.addEventListener('open', function(e) {
  console.log("Events Connected");
 }, false);
 source.addEventListener('error', function(e) {
  if (e.target.readyState != EventSource.OPEN) {
    console.log("Events Disconnected");
  }
 }, false);
 
 source.addEventListener('message', function(e) {
  console.log("message", e.data);
 }, false);
 
 source.addEventListener('new_readings', function(e) {
  console.log("new_readings", e.data);
  var obj = JSON.parse(e.data);
  document.getElementById("g"+obj.id).innerHTML = obj.g.toFixed(2);
  document.getElementById("rt"+obj.id).innerHTML = obj.readingId;
  document.getElementById("rh"+obj.id).innerHTML = obj.readingId;
 }, false);
}

  if (obj.g.toFixed(2) > 100) {
      document.getElementById("rg1").style.color = "red";
  }
    if (obj.g.toFixed(2) <= 100 && obj.g.toFixed(2) > 50) {
      document.getElementById("rg1").style.color = "orange";
  }
    if(obj.g.toFixed(2) <= 50){
      document.getElementById("rg1").style.color = "green";
   }

</script>
</body>
</html>)rawliteral";

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Gerät als WiFi Bridge aktivieren
  WiFi.mode(WIFI_AP_STA);
  
  // WiFi einstellungen vornehmen
  WiFi.begin(ssid, pw);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Verbinden mit Lokalen WiFi");
  }
  Serial.print("Station IP Addresse: ");
  Serial.println(WiFi.localIP());
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
   
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);
  server.begin();
}
 
void loop() {
  static unsigned long lastEventTime = millis();
  static const unsigned long EVENT_INTERVAL_MS = 5000;
  if ((millis() - lastEventTime) > EVENT_INTERVAL_MS) {
    events.send("ping",NULL,millis());
    lastEventTime = millis();
  }
}