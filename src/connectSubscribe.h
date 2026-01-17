#ifndef connectSubscribe_h
#define connectSubscribe_h
#include "Arduino.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "defines.h"

extern uint8_t c;
extern bool serial;
extern WiFiClient wificlient;
// create MQTT object
extern PubSubClient client;
extern bool serial, connection;
extern unsigned long tkeepConnect;
extern unsigned int connectTime;
extern ESP8266WiFiMulti wifiMulti;
void connectSubscribe();
// void getFeedLatest();
void checkConnection();

#endif