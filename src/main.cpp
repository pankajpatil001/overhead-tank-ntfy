#include "definitions.h"

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  if(serial) Serial.begin(115200);      
  delay(10);
  if(serial) Serial.println();
  delay(10);
  WiFi_httpStuff(); //handles everything wrt wifi and http server

  client.setServer(SERVER, SERVERPORT);
  client.setCallback(callback);
  sendNtfyMessage(NTFY_TOPIC, STARTUP_NTFN);
}

//
void loop() {
  httpServer.handleClient();
  // MDNS.update();

  checkConnection();
  connectSubscribe();
  publishFeeds();
  getMainTankWaterLevel();

  client.loop();  
  yield();
}