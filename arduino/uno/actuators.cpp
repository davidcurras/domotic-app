#include <SPI.h>
#include "actuators.h"

const int ACT_SPEAKER_PIN = 6;     //D6  - LED (replace with speaker)
const int ACT_LED1_PIN = 9;        //D9  - LED for Max Light
const int ACT_LED2_PIN = 13;       //D13 - LED for PIR2
const int ACT_IRRIGATION_PIN = 14; //D13 - Irrigation Act

void Actuators::Init() {
  pinMode(ACT_SPEAKER_PIN, OUTPUT);
  pinMode(ACT_LED1_PIN, OUTPUT);
  pinMode(ACT_LED2_PIN, OUTPUT);
  pinMode(ACT_IRRIGATION_PIN, OUTPUT);
};

void Actuators::SetSpeaker(int speakerState) {
  digitalWrite(ACT_SPEAKER_PIN, speakerState);
};

void Actuators::SetLed1(int led1State) {
  digitalWrite(ACT_LED1_PIN, led1State);
};

void Actuators::SetLed2(int led2State) {
  digitalWrite(ACT_LED2_PIN, led2State);
};

int Actuators::GetIrrigationState() {
  return digitalRead(ACT_IRRIGATION_PIN);
};
