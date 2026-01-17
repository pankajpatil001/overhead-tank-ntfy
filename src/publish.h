#ifndef publish_h
#define publish_h
#include "Arduino.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "defines.h"
// #include "temperature.h"

extern unsigned long tkeepMainTankLevel, tkeepRssi;
extern unsigned int rssiTime, mainTankLevelTime, mainTankWaterLevel;
extern PubSubClient client;
extern char valueStr[100];
extern bool serial;

void publishFeeds();

#endif