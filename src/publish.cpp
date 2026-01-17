#include "publish.h"

void publishFeeds(){
    
  //------------------------RSSI-----------------------------
  if (millis() - tkeepRssi > rssiTime && client.connected()) {
    String str = "Overhead Tank Monitor Device IP "; 
    str+= WiFi.localIP().toString();
    str+= ", RSSI ";
    str+= (String)WiFi.RSSI();
    str+= " dBm\n";
    str.toCharArray(valueStr, 80);
    Serial.println(str);
    client.publish(PREAMBLE MESSAGES, valueStr);
    tkeepRssi = millis();
  }
  //------------------------RSSI-----------------------------

  if (millis() - tkeepMainTankLevel > mainTankLevelTime && client.connected()) {
    String str = (String)mainTankWaterLevel;
    str.toCharArray(valueStr, 70);
    Serial.println(str);
    if (mainTankWaterLevel != 0) client.publish(PREAMBLE MAINTANK, valueStr);
    tkeepMainTankLevel = millis();
  }

  // if (client.connected() && firstTime && coolerState) {
  //   String str = "ON";
  //   str.toCharArray(valueStr, 10);
  //   client.publish(PREAMBLE COOLER, valueStr);
  //   firstTime = LOW;
  // }
}