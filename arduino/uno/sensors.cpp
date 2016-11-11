#include <SPI.h>
#include "sensors.h"
#include "actuators.h"

const int SENS_LIGHT_PIN = 0; //A0  - Light sensor (LDR)
const int SENS_PIR1_PIN = 3;  //D3  - PIR sensor 1 (turns on alarm)
const int SENS_PIR2_PIN = 7;  //D7  - PIR sensor 2 (turns on light)
const int MAX_LIGHT = 150;    //Max LDR value for SENS_LIGHT_PIN

void Sensors::Init() {
  pinMode(SENS_PIR1_PIN, INPUT);
  pinMode(SENS_PIR2_PIN, INPUT);
  pinMode(SENS_LIGHT_PIN, INPUT);
};

/**
 * @see http://programarfacil.com/podcast/48-sensor-de-temperatura-en-arduino
 */
int Sensors::GetLight() {
  return (analogRead(SENS_LIGHT_PIN) * 250.0) / 1024.0;
};

int Sensors::GetPir1() {
  return digitalRead(SENS_PIR1_PIN);
};

int Sensors::GetPir2() {
  return digitalRead(SENS_PIR2_PIN);
};

void Sensors::WatchLight() {
  int light = Sensors::GetLight();
  if (light > MAX_LIGHT) {
    Actuators::SetLedLight(HIGH);
  } else {
    Actuators::SetLedLight(LOW);
  }
};

void Sensors::WatchPIR1() {
  int pirState = Sensors::GetPir1();
  Actuators::SetSpeaker(pirState);
};

void Sensors::WatchPIR2() {
  int pirState = Sensors::GetPir2();
  Actuators::SetLedPir(pirState);
};
