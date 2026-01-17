#include "waterlevel.h"


uint8_t getWaterLevelCM(uint16_t dly) {
    // uint8_t d = 0;
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); 

    digitalWrite(trigPin, HIGH); // turn on the Trigger to generate pulse
    delayMicroseconds(10); // keep the trigger "ON" for 10 ms to generate pulse
    digitalWrite(trigPin, LOW); // Turn off the pulse trigger to stop pulse

    // If pulse reached the receiver echoPin
    // become high Then pulseIn() returns the
    // time taken by the pulse to reach the receiver
    unsigned long duration = pulseIn(echoPin, HIGH);
    unsigned int waterLevelCM = duration * 0.0344 / 2; 
    
    // digitalWrite(trigP, LOW);   // Makes trigPin low
    // delayMicroseconds(2);       // 2 micro second delay 
    
    // digitalWrite(trigP, HIGH);  // tigPin high
    // delayMicroseconds(15);      // trigPin high for 10 micro seconds
    // digitalWrite(trigP, LOW);   // trigPin low
    
    // duration = pulseIn(echoP, HIGH);   //Read echo pin, time in microseconds
    // d = duration*0.0343/2;        //Calculating actual/real distance
    // if(serial) Serial.print("Temp Distance = ");        //Output distance on arduino serial monitor 
    // if(serial) Serial.println(d);
    delay(dly);
    return waterLevelCM;
}

uint16_t filteredAvgWaterLevel(uint16_t dly, uint8_t sample, uint8_t tolerance = 3, uint8_t minClusterSize = 3) {
    uint16_t readings[MAX_SAMPLES];
  
    if (sample > MAX_SAMPLES) sample = MAX_SAMPLES; // Limit to max samples
  
    // Step 1: Collect samples
    for (uint8_t i = 0; i < sample; i++) {
      readings[i] = getWaterLevelCM(dly);
      delay(1); // Small delay between readings
    }
  
    uint8_t bestCount = 0;
    uint16_t bestSum = 0;
  
    for (uint8_t i = 0; i < sample; i++) {
      uint8_t count = 1;
      uint16_t sum = readings[i];
  
      for (uint8_t j = 0; j < sample; j++) {
        if (i != j && abs(readings[i] - readings[j]) <= tolerance) {
          count++;
          sum += readings[j];
        }
      }
      
      if (count > bestCount) {
        bestCount = count;
        bestSum = sum;
      }
    }
  
    // Step 4: Return average of the best cluster
    if (bestCount >= minClusterSize) {
      return bestSum / bestCount;
    } else {
      // If no cluster meets the minimum size, return the average of all readings
      uint32_t total = 0;
      for (uint8_t i = 0; i < sample; i++) {
        total += readings[i];
      }
      return total / sample;
    }
}


void getMainTankWaterLevel() {
    if (millis() - tkeepWaterLevel > waterLevelTime) {

        unsigned int avgWaterLevelCM = filteredAvgWaterLevel(50, 20, 3, 8); // 50ms delay for the sensor to stabilize

        // if (client.connected()) {
        //   String str = (String)avgWaterLevelCM;
        //   str.toCharArray(valueStr, 10);
        //   client.publish(PREAMBLE HUMIDITY, valueStr);
        // }
        
        if (avgWaterLevelCM > mainTankEmptyReading + 10) return;
        if (avgWaterLevelCM < mainTankFullReading - 10) return;
        if (!firstTime && ((mainTankWaterLevel - prevMainTankWaterLevel) > errorMargin)) return;
        if (!firstTime && ((prevMainTankWaterLevel - mainTankWaterLevel) > errorMargin)) return;

        mainTankWaterLevel = map(avgWaterLevelCM, mainTankEmptyReading, mainTankFullReading, 1, 100);
        // if (!firstTime && (mainTankWaterLevel > prevMainTankWaterLevel ? mainTankWaterLevel - prevMainTankWaterLevel : prevMainTankWaterLevel - mainTankWaterLevel) > errorMargin) return;
        // if (abs(mainTankWaterLevel - prevMainTankWaterLevel) > errorMargin) return;

        mainTankWaterLevel = constrain(mainTankWaterLevel, 1, 100);
        prevMainTankWaterLevel = mainTankWaterLevel;

        Serial.print("Water Level: ");
        Serial.print(mainTankWaterLevel);
        Serial.println(" %");

        // mainTankWaterLevel = avgWaterLevelCM; // activate only for debugging
        firstTime = LOW;
        tkeepWaterLevel = millis();
    }
}