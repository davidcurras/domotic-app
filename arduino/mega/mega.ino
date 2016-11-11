#include <SPI.h>
#include <Ethernet.h>
#include "network.h"
#include "sensors.h"
#include "actuators.h"

void setup() {
  Serial.begin(9600);
  Actuators::Init();
  Sensors::Init();
  Network::Init();
};

void loop() {
  Network::Update();
  Sensors::WatchFlame();
  Sensors::WatchGasLevel();
  Sensors::WatchTemperature();
};
