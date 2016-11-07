#include <SPI.h>
#include "sensors.h"
#include "actuators.h"

void setup() {
  Sensors::Init();
  Actuators::Init();
  Serial.begin(9600);
}

void loop() {
  Sensors::WatchLight();
  Sensors::WatchPIR1();
  Sensors::WatchPIR2();
  Sensors::GetGroundHumidity();
  Actuators::GetIrrigationState();
}
