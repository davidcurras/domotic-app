#include <SPI.h>
#include "sensors.h"
#include "actuators.h"

const int SENS_PIR1_PIN = 3;      //D3  - PIR sensor 1
const int SENS_PIR2_PIN = 7;      //D7  - PIR sensor 2
const int SENS_LIGHT_PIN = 0;     //A0  - Light sensor
const int SENS_HUMIDITY_PIN = A2; //A2  - Ground humidity sensor

//Este valor hara que el LED cambie de estado a una determinada
//luminosidad (podeis con distintos valores para ajustar la sensibilidad)
const int MAX_LIGHT = 150;

void Sensors::Init() {
  pinMode(SENS_PIR1_PIN, INPUT);
  pinMode(SENS_PIR2_PIN, INPUT);
  pinMode(SENS_LIGHT_PIN, INPUT);
  pinMode(SENS_HUMIDITY_PIN, INPUT);
};

int Sensors::GetGroundHumidity() {
  return analogRead(SENS_HUMIDITY_PIN);
};

/**
 * @see http://programarfacil.com/podcast/48-sensor-de-temperatura-en-arduino
 */
void Sensors::WatchLight() {
  int light = (analogRead(SENS_LIGHT_PIN) * 250.0) / 1024.0;
  if (light > MAX_LIGHT) {
    Actuators::SetLed1(HIGH);
  } else {
    Actuators::SetLed1(LOW);
  }
};

void Sensors::WatchPIR1() {
  int pirState = digitalRead(SENS_PIR1_PIN);
  Actuators::SetSpeaker(pirState);
};

void Sensors::WatchPIR2() {
  int pirState = digitalRead(SENS_PIR2_PIN);
  Actuators::SetLed2(pirState);
};
