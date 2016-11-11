#include <SPI.h>
#include "actuators.h"

const int ACT_SPEAKER_PIN = 6;   //D6  - LED (replace with speaker)
const int ACT_LED_LIGHT_PIN = 9; //D9  - LED for Max Light
const int ACT_LED_PIR_PIN = 13;  //D13 - LED for PIR2

void Actuators::Init() {
  pinMode(ACT_SPEAKER_PIN, OUTPUT);
  pinMode(ACT_LED_LIGHT_PIN, OUTPUT);
  pinMode(ACT_LED_PIR_PIN, OUTPUT);
};

void Actuators::SetSpeaker(int speakerState) {
  int current = digitalRead(ACT_SPEAKER_PIN);
  if(current != speakerState) {
    digitalWrite(ACT_SPEAKER_PIN, speakerState);
  }
};

int Actuators::GetSpeaker() {
  return digitalRead(ACT_SPEAKER_PIN);
};

void Actuators::SetLedLight(int led1State) {
  int current = digitalRead(ACT_LED_LIGHT_PIN);
  if(current != led1State) {
    digitalWrite(ACT_LED_LIGHT_PIN, led1State);
  }
};

int Actuators::GetLedLight() {
  return digitalRead(ACT_LED_LIGHT_PIN);
};

void Actuators::SetLedPir(int led2State) {
  int current = digitalRead(ACT_LED_PIR_PIN);
  if(current != led2State) {
    digitalWrite(ACT_LED_PIR_PIN, led2State);
  }
};

int Actuators::GetLedPir() {
  return digitalRead(ACT_LED_PIR_PIN);
};
