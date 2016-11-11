#include <SPI.h>
#include "DHT.h"
#include "sensors.h"
#include "actuators.h"

#define DHT_PIN 3
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

const int SENS_GAS_PIN = 0;       //A0  - Gas quality sensor MQ135
const int SENS_FLAME_PIN = 1;     //D1  - Flame Detector
const int SENS_HUMIDITY_PIN = A1; //A1  - Ground humidity sensor
const int MAX_TEMP = 27;          //Max temperature for turn on AUTO_FAN
const int MAX_GAS_LEVEL = 300;    //Max gas level for turn on led alert

void Sensors::Init() {
  dht.begin();
  pinMode(SENS_GAS_PIN, INPUT);
  pinMode(SENS_FLAME_PIN, INPUT);
  pinMode(SENS_HUMIDITY_PIN, INPUT);
};

int Sensors::GetGasLevel() {
  return analogRead(SENS_GAS_PIN);
};

int Sensors::GetGasType() {
  int gasLevel = Sensors::GetGasLevel();
  return (int) (gasLevel / 100);
};

int Sensors::GetFlame() {
  return digitalRead(SENS_FLAME_PIN);
};

float Sensors::GetHumidity() {
  return dht.readHumidity();
};

float Sensors::GetTemperature() {
  return dht.readTemperature();
};

float Sensors::GetGroundHumidity() {
  return (100 * analogRead(SENS_HUMIDITY_PIN)) / 1024;
};

void Sensors::WatchGasLevel() {
  if(Sensors::GetGasLevel() > MAX_GAS_LEVEL) {
    Actuators::SetGasLed(HIGH);
  } else {
    Actuators::SetGasLed(LOW);
  }
};

void Sensors::WatchFlame() {
  if(Sensors::GetFlame() == HIGH) {
    Actuators::SetFireLed(HIGH);
  } else {
    Actuators::SetFireLed(LOW);
  }
};

void Sensors::WatchTemperature() {
  if (Sensors::GetTemperature() > MAX_TEMP) {
    Actuators::SetAutoFan(HIGH);
  } else {
    Actuators::SetAutoFan(LOW);
  }
};
