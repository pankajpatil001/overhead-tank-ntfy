#ifndef ntfy_h
#define ntfy_h
#include "Arduino.h"
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

extern WiFiClientSecure wificlientsecure;
extern HTTPClient rpihttp; //HTTP client for RPI server
extern bool serial, wifiConnected;

void sendNtfyMessage(const String& topic, const String& message);

#endif