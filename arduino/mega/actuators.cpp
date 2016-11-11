#include <SPI.h>
#include "actuators.h"

const int ACT_AUTO_FAN_PIN = 7;     //D7  - Temp > 27c
const int ACT_IRRIGATION_PIN = 12;  //D12 - Irrigation pin handler
const int ACT_GAS_LED_PIN = 13;     //D13 - Led high butano levels
const int ACT_FIRE_LED_PIN = 25;    //D25 - Led when fire
const int ACT_FAN_PIN = 5;          //D20 - Manual Fan
const int ACT_LIGHT_PIN = 8;        //D8  - Led on pin 8
const int ACT_LED_2 = 2;            //D2  - Led on pin 2
const int ACT_LED_6 = 6;            //D6  - Led on pin 6
const int ACT_LED_9 = 9;            //D9  - Led on pin 9
//::LEDS[

void Actuators::Init() {
  pinMode(ACT_AUTO_FAN_PIN, OUTPUT);
  pinMode(ACT_IRRIGATION_PIN, OUTPUT);
  pinMode(ACT_GAS_LED_PIN, OUTPUT);
  pinMode(ACT_FIRE_LED_PIN, OUTPUT);
  pinMode(ACT_FAN_PIN, OUTPUT);
  pinMode(ACT_LIGHT_PIN, OUTPUT);
  pinMode(ACT_LED_2, OUTPUT);
  pinMode(ACT_LED_6, OUTPUT);
  pinMode(ACT_LED_9, OUTPUT);
};

void Actuators::SetAutoFan(int fanState) {
  int current = digitalRead(ACT_AUTO_FAN_PIN);
  if(current != fanState) {
    Serial.println("SetAutoFan" + String(fanState));
    digitalWrite(ACT_AUTO_FAN_PIN, fanState);
  }
};

int Actuators::GetAutoFan() {
  return digitalRead(ACT_AUTO_FAN_PIN);
};

void Actuators::SetIrrigation(int irrigationState) {
  int current = digitalRead(ACT_IRRIGATION_PIN);
  if(current != irrigationState) {
    Serial.println("SetIrrigation" + String(irrigationState));
    digitalWrite(ACT_IRRIGATION_PIN, irrigationState);
  }
};

int Actuators::GetIrrigation() {
  return digitalRead(ACT_IRRIGATION_PIN);
};

void Actuators::SetGasLed(int ledState) {
  int current = digitalRead(ACT_GAS_LED_PIN);
  if(current != ledState) {
    Serial.println("SetGasLed" + String(ledState));
    digitalWrite(ACT_GAS_LED_PIN, ledState);
  }
};

int Actuators::GetGasLed() {
  return digitalRead(ACT_GAS_LED_PIN);
};

void Actuators::SetFireLed(int ledState) {
  int current = digitalRead(ACT_FIRE_LED_PIN);
  if(current != ledState) {
    Serial.println("SetFireLed" + String(ledState));
    digitalWrite(ACT_FIRE_LED_PIN, ledState);
  }
};

int Actuators::GetFireLed() {
  return digitalRead(ACT_FIRE_LED_PIN);
};

void Actuators::SetFan(int fanState) {
  int current = digitalRead(ACT_FAN_PIN);
  if(current != fanState) {
    Serial.println("SetFan" + String(fanState));
    digitalWrite(ACT_FAN_PIN, fanState);
  }
};

int Actuators::GetFan() {
  return digitalRead(ACT_FAN_PIN);
};

void Actuators::SetLight(int lightState) {
  int current = digitalRead(ACT_LIGHT_PIN);
  if(current != lightState) {
    Serial.println("SetFan" + String(lightState));
    digitalWrite(ACT_LIGHT_PIN, lightState);
  }
};

int Actuators::GetLight() {
  return digitalRead(ACT_LIGHT_PIN);
};

void Actuators::SetLed(int pin, int ledState) {
  if(pin == 2 || pin == 6 || pin == 9) {
    Serial.println("SetLed" + String(pin) + String(ledState));
    digitalWrite(pin, ledState);
  }
};

int Actuators::GetLed(int pin) {
  if(pin == 2 || pin == 6 || pin == 9) {
    return digitalRead(pin);
  } else {
    return 0;
  }
};
