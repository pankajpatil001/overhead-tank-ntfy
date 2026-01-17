#ifndef webupdater_h
#define webupdater_h
#include "Arduino.h"

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <PubSubClient.h>
#include "defines.h"

extern WiFiClient wificlient;
// create MQTT object
extern PubSubClient client;
extern const char* host;
extern bool serial;

extern ESP8266WiFiMulti wifiMulti;
extern ESP8266WebServer httpServer; //Choose any number you want, just add this after your ip adrs
extern ESP8266HTTPUpdateServer httpUpdater; //http://<local-ip>:<any-number>/ as server address

extern const char* loginIndex;
extern const char* serverIndex;


void WiFi_httpStuff();

#endif