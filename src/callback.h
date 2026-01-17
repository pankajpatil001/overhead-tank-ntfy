#ifndef callback_h
#define callback_h
#include "Arduino.h"
#include <EEPROM.h>
#include "defines.h"

extern bool serial;
extern String incoming[100];

void callback(char* topic, byte * data, unsigned int length);

#endif