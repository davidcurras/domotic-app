#include <SPI.h>
#include "actuators.h"

const int ACT_FAN_PIN = 7;         //D7  - Temp > 27c
const int ACT_IRRIGATION_PIN = 12; //D12 - Irrigation pin handler
const int ALARM_GAS_FIRE_PIN = 13; //D13 - Alarm when fire or high butano levels
const int ACT_CO2_HIGH_PIN = 11;   //D11 - CO2 High actuator
const int ACT_BUTANO_PIN = 15;     //D15 - Butano actuator
const int ACT_CO2_LOW_PIN = 20;    //D20 - CO2 Low actuator

// LEDS array to handle each led state
byte Actuators::LEDS[5] = { 2, 9, 6, 5, 8};
byte led[ sizeof(Actuators::LEDS) ] = { 0 };

void Actuators::Init() {
  pinMode(ACT_FAN_PIN, OUTPUT);
  pinMode(ACT_CO2_LOW_PIN, OUTPUT);
  pinMode(ACT_CO2_HIGH_PIN, OUTPUT);
  pinMode(ACT_BUTANO_PIN, OUTPUT);
  pinMode(ALARM_GAS_FIRE_PIN, OUTPUT);
  pinMode(ACT_IRRIGATION_PIN, INPUT);
  digitalWrite(ACT_CO2_LOW_PIN, LOW);
  digitalWrite(ACT_CO2_HIGH_PIN, LOW);
  digitalWrite(ACT_BUTANO_PIN, LOW);
  // set up the LED pins as outputs
  for (byte index = 0; index < sizeof(Actuators::LEDS); index++) {
    pinMode(Actuators::LEDS[index], OUTPUT);
  }
};

void Actuators::SetFan(int fanState) {
  int current = digitalRead(ACT_FAN_PIN);
  if(current != fanState) {
    digitalWrite(ACT_FAN_PIN, fanState);
  }
};

void Actuators::SetFireAlarm(int alarmState) {
  int current = digitalRead(ALARM_GAS_FIRE_PIN);
  if(current != alarmState) {
    digitalWrite(ALARM_GAS_FIRE_PIN, alarmState);
  }
};

void Actuators::SetLed(int index, int ledState) {
  led[index] = ledState;
};

bool Actuators::SetGas(int gasType) {
  int co2Low, co2High, butano;
  bool fireAlarmState = false;
  switch(gasType) {
    case 0:
      co2Low = co2High = butano = LOW;
      break;
    case 1:
      co2High = butano = LOW;
      co2Low = HIGH;
      break;
    case 2:
    case 3:
      co2Low = butano = LOW;
      co2High = HIGH;
      break;
    case 4:
    default:
      co2Low = co2High = LOW;
      butano = HIGH;
      fireAlarmState = true;
      break;
  }
  int current = digitalRead(ACT_CO2_LOW_PIN);
  if(current != co2Low) {
    digitalWrite(ACT_CO2_LOW_PIN, co2Low);
  }
  current = digitalRead(ACT_CO2_HIGH_PIN);
  if(current != co2High) {
    digitalWrite(ACT_CO2_HIGH_PIN, co2High);
  }
  current = digitalRead(ACT_BUTANO_PIN);
  if(current != butano) {
    digitalWrite(ACT_BUTANO_PIN, butano);
  }
  return fireAlarmState;
};

String Actuators::GetIrrigationState() {
  if(digitalRead(ACT_IRRIGATION_PIN) == HIGH) {
    return "\t\"irrigation\": true,\n";
  } else {
    return "\t\"irrigation\": false,\n";
  }
};

String Actuators::GetFanState() {
  if(digitalRead(ACT_FAN_PIN) == HIGH) {
    return "\t\"fan\": true\n";
  } else {
    return "\t\"fan\": false\n";
  }
};

String Actuators::GetLedsState() {
  String data = "";
  for (byte i = 0; i < sizeof(Actuators::LEDS); i++) {
    data += "\t\"led"+String(i)+"\": "+String(Actuators::LEDS[i])+",\n";
  }
  return data;
};
