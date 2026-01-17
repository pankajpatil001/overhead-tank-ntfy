#include "ntfy.h"

void sendNtfyMessage(const String& topic, const String& message) {
  if (!wifiConnected) {
    Serial.println("WiFi not connected");
    return;
  }

//   WiFiClientSecure client;
  wificlientsecure.setInsecure();  // ntfy.sh uses HTTPS

//   HTTPClient https;

  String url = "https://ntfy.sh/" + topic;
  Serial.println("POST -> " + url);

  if (rpihttp.begin(wificlientsecure, url)) {
    rpihttp.addHeader("Content-Type", "text/plain");

    int httpCode = rpihttp.POST(message);

    if (httpCode > 0) {
      Serial.printf("HTTP Code: %d\n", httpCode);
      Serial.println("Response:");
      Serial.println(rpihttp.getString());
    } else {
      Serial.printf("POST failed: %s\n",
        rpihttp.errorToString(httpCode).c_str());
    }

    rpihttp.end();
  } else {
    Serial.println("HTTPS begin failed");
  }
}