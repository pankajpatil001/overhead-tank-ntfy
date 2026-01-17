#include "temperature.h"

void chkTemp() {
  if(millis() - tkeepchkTemp > chkTempTime && smart == HIGH) {
    temp = getTemperature();
    Serial.print("Temperature:");
    Serial.print(temp);
    Serial.println(" C");
    // if(temp > (float)setTemp + 1.5 && fan == LOW){
    //   if (speedStat == LOW) {
    //     Serial.println("Cooler Turned On at Low Speed");
    //     digitalWrite(FRLO, HIGH); //rum fan at slow speed
    //     digitalWrite(FRHI, LOW);
    //     if(io.status() == AIO_CONNECTED) FAN->save("ON");
    //     else Serial.println("Unable to publish due to Disconnection.");
    //   } 
    //   else if (speedStat == HIGH) {
    //     Serial.println("Cooler Turned On at High Speed");
    //     digitalWrite(FRHI, HIGH); //rum fan at high speed
    //     digitalWrite(FRLO, LOW);
    //     if(io.status() == AIO_CONNECTED) FAN->save("ON");
    //     else Serial.println("Unable to publish due to Disconnection.");
    //   }
    //   fan = HIGH;
    // }
    // else if(temp < (float)setTemp - 0.5 && fan == HIGH){
    //   Serial.println("Cooler Turned Off");
    //   digitalWrite(FRHI, LOW); //turn off fan
    //   digitalWrite(FRLO, LOW);
    //   if(io.status() == AIO_CONNECTED) FAN->save("OFF");
    //   else Serial.println("Unable to publish due to Disconnection.");
    //   fan = LOW;
    // }
    tkeepchkTemp = millis();
  }
}


float getTemperature() {

  val = analogRead(A0); //get the sensor analog value
  double Temp = (double)val * 100.0 / 1024.0; //set 500 for arduino and 100 for esp12
//   Serial.print("Temperature2:");
//   Serial.print(Temp);
//   Serial.println(" C");
  lmTemp = 0;

  if (ti == 0) ts[0] = Temp;
  else if (ti > 0) {
    for (uint8_t j = ti; j > 0 ; j--) {
      ts[j] = ts[j - 1];
    }
    ts[0] = Temp;
  }

  for (uint8_t j = 0; j <= ti; j++) {
    lmTemp += ts[j];
  }

  lmTemp = lmTemp / (ti + 1);
  if (ti < 19) ti++;

  return lmTemp;
}
