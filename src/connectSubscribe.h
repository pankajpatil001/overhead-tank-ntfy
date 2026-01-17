#ifndef connectSubscribe_h
#define connectSubscribe_h
#include "Arduino.h"

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
// #include <WiFiClient.h>
#include <PubSubClient.h>
#include "defines.h"

extern uint8_t c;
extern bool serial;
extern WiFiClientSecure wificlientsecure;
extern uint8_t wifiReconnectAttemptCount;
extern bool serial, wifiConnected;
// create MQTT object
extern PubSubClient client;
extern bool serial, connection;
extern unsigned long tkeepConnect, lastReconnectAttempt;
extern unsigned int connectTime;
extern char SERVER[16];
void connectSubscribe();
// void getFeedLatest();
void checkConnection();

#endif