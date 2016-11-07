#include <SPI.h>
#include "DHT.h"
#include "sensors.h"
#include "actuators.h"

const int SENS_GAS_PIN = 0;       //A0  - Gas quality sensor MQ135
const int SENS_FLAME_PIN = 1;     //D1  - Flame Detector
const int SENS_HUMIDITY_PIN = A1; //A1  - Ground humidity sensor

void Sensors::Init() {
  pinMode(SENS_FLAME_PIN, INPUT);
};

String Sensors::GetHumidity(DHT dht) {
  float humidity = dht.readHumidity();
  return "\t'humidity': '"+String(humidity)+"',\n";
};

String Sensors::GetTemperature(DHT dht) {
  float temperature = dht.readTemperature();
  return "\t'temperature': '"+String(temperature)+"C',\n";
};

String Sensors::GetFlame() {
  if(digitalRead(SENS_FLAME_PIN) == HIGH) {
    return "\t'fire': true,\n";
  } else {
    return "\t'fire': false,\n";
  }
};

String Sensors::GetGroundHumidity() {
  int humidity = (100 * analogRead(SENS_HUMIDITY_PIN)) / 1024;
  return "\t'groundHumidity': '"+String(humidity)+"%',\n";
};

String Sensors::GetGasLevel() {
  int gasLevel = analogRead(SENS_GAS_PIN);
  int gasType = (int) (gasLevel / 100);
  String data = "\t'gas': '"+String(gasLevel)+"ppm',\n";
  data += "\t'gasState': ";
  switch(gasType) {
    case 0:
      data += "'normal',\n";
      break;
    case 1:
      data += "'low-co2',\n";
      break;
    case 2:
    case 3:
      data += "'high-co2',\n";
      break;
    case 4:
    default:
      data += "'high-butano',\n";
      break;
  }
  return data;
};

void Sensors::WatchFlame() {
  if(digitalRead(SENS_FLAME_PIN) == HIGH) {
    Actuators::SetFireAlarm(HIGH);
  } else {
    Actuators::SetFireAlarm(LOW);
  }
};

void Sensors::WatchGasLevel() {
  int gasType = (int) (analogRead(SENS_GAS_PIN) / 100);
  bool fireAlarmState = gasType;
  Actuators::SetFireAlarm(fireAlarmState);
};

void Sensors::WatchTemperature(DHT dht) {
  if (dht.readTemperature() < 25) {
    Actuators::SetFan(LOW);
  } else {
    Actuators::SetFan(HIGH);
  }
};
