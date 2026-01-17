#ifndef coolerWater_h
#define coolerWater_h
#include "Arduino.h"
#include <PubSubClient.h>
#include "defines.h"

#define MAX_SAMPLES 20

extern unsigned long tkeepWaterLevel;
extern unsigned long waterLevelTime, waterLevelTimeHigh, waterLevelTimeLow;
extern bool firstTime;
extern PubSubClient client;
extern char valueStr[100];
extern unsigned int mainTankWaterLevel, mainTankFullReading, mainTankEmptyReading, prevMainTankWaterLevel, errorMargin;

void getMainTankWaterLevel();

#endif