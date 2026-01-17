#ifndef temperature_h
#define temperature_h
#include "Arduino.h"
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "defines.h"

extern unsigned long tkeepchkTemp;//, tkeepRssi, tkeepLight;//, tkeepHum, tkeepUSpub;
// extern unsigned int rssiTime;//, tempTime, lightTime, humTime, lightinty, uspubTime;
extern unsigned int chkTempTime;
// // extern unsigned int doorTime = 1000, pirTime = 1000, usTime = 2000, uspubTime = 10000, buzzTime = 5000;
extern float temp;//, hum, prevTemp, prevHum;
// // extern bool firstTime, pirState, doorState, connection, lightStatus;
// extern PubSubClient client;
// extern char valueStr[100];
// // extern unsigned int distance, prevDistance;
extern bool smart;

extern uint8_t ti;
extern int val;
extern double t;
extern double lmTemp, t1;
extern double ts[20];

void chkTemp();
float getTemperature();

#endif