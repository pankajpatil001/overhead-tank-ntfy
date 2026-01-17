#include "connectSubscribe.h"

void connectSubscribe(){
  if (!client.connected() && millis() - tkeepConnect > connectTime) {
    if (WiFi.status() != WL_CONNECTED) {
      if(serial) Serial.println("Connecting to WiFi!");
      wifiMulti.run();
      delay(1000);
      c++;
      if(c>20) ESP.restart();
    }
    else {
      c=0;
      if(serial) Serial.println("Attempting MQTT connection...");
      // Attempt to connect
      if (client.connect("pankaj", MQTT_USERNAME, MQTT_KEY)) {
        if(serial) Serial.println("connected");
        // ... and resubscribe
        Serial.println("Subscribing again...");
        Serial.println(PREAMBLE ON_TIME);
        Serial.println(PREAMBLE OFF_TIME);
        if (client.subscribe(PREAMBLE ON_TIME, 1)) Serial.println("Subscribed to ON Time");
        if (client.subscribe(PREAMBLE OFF_TIME, 1)) Serial.println("Subscribed to OFF Time");
        // client.subscribe(PREAMBLE OFF_TIME, 1);
  
        delay(1);
        connection = HIGH;
        // getFeedLatest(); //get latest values of feed
      } 
      else {
        if(serial) Serial.print("Failed, rc=");
        if(serial) Serial.print(client.state());
        if(serial) Serial.println(" Retrying soon...!!!");
      }
    }
    tkeepConnect = millis();
  }
}


// void getFeedLatest(){
//   client.publish(PREAMBLE LIGHTS GETLATEST, "\0");
//   delay(1);
//   client.publish(PREAMBLE ALARM GETLATEST, "\0");
//   delay(1);
//   client.publish(PREAMBLE BROODER GETLATEST, "\0");
//   delay(1);
//   client.publish(PREAMBLE MOTOR GETLATEST, "\0");
//   delay(1);
// }

void checkConnection(){
    //----Connection LED-----
  if(client.connected() && connection == LOW) {
    c=0;
    // digitalWrite(LED, LOW); //Connected
    connection = HIGH;
  }
  else if(!client.connected() && connection == HIGH){
    // digitalWrite(LED, HIGH); //Not Connected
    Serial.println("Not connected.");
    connection = LOW;
  }
  //-----------------------
}