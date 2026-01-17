#ifndef publish_h
#define publish_h
#include "Arduino.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "defines.h"
// #include "temperature.h"

extern unsigned long tkeepMainTankLevel, tkeepRssi, tkeepLight;//, tkeepHum, tkeepUSpub;
extern unsigned int rssiTime, mainTankLevelTime, mainTankWaterLevel;//, lightTime, humTime, lightinty, uspubTime;
// extern unsigned int prevLightinty;
// extern unsigned int doorTime = 1000, pirTime = 1000, usTime = 2000, uspubTime = 10000, buzzTime = 5000;
// extern float temp;//, hum, prevTemp, prevHum;
// extern bool firstTime, coolerState;//, pirState, doorState, connection, lightStatus;
extern PubSubClient client;
extern char valueStr[100];
// extern unsigned int distance, prevDistance;
extern bool serial;


void publishFeeds();

#endif