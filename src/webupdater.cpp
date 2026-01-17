#include "webupdater.h"

void WiFi_httpStuff(){
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(ssid1, pwd1); 
  wifiMulti.addAP(ssid2, pwd2);
  wifiMulti.addAP(ssid3, pwd3);
  wifiMulti.addAP(ssid4, pwd4);
  // wifiMulti.addAP(ssid5, pwd5);
  // wifiMulti.addAP(ssid6, pwd6);
  wifiMulti.addAP(ssid7, pwd7);
  
  Serial.println("Connecting Wifi...");
  while (wifiMulti.run() != WL_CONNECTED && millis() < 2000) {
    if(serial) Serial.println(".");
    delay(400);
  }
  MDNS.begin(host);

  httpUpdater.setup(&httpServer);

  httpServer.on("/", HTTP_GET, []() {
    httpServer.sendHeader("Connection", "close");
    httpServer.send(200, "text/html", loginIndex);
  });
  httpServer.on("/serverIndex", HTTP_GET, []() {
    httpServer.sendHeader("Connection", "close");
    httpServer.send(200, "text/html", serverIndex);
  });
  /*handling uploading firmware file */
  httpServer.on("/update", HTTP_POST, []() {
    httpServer.sendHeader("Connection", "close");
    httpServer.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, []() {
    // HTTPUpload& upload = httpServer.upload();
    httpServer.upload();
    
  });
  
  httpServer.begin();
  
  MDNS.addService("http", "tcp", 80);
  if(wifiMulti.run() == WL_CONNECTED) {
      if(serial) Serial.println("WiFi connected...!!!");
      if(serial) Serial.println("IP address: ");
      if(serial) Serial.println(WiFi.localIP());
      
      if(serial) Serial.print("HTTPUpdateServer ready! Open http://");
      if(serial) Serial.print(WiFi.localIP());
      if(serial) Serial.println("/ in your browser.");
  }
  else {
    if(serial) Serial.println("WiFi not connected...!!!");
  }

}