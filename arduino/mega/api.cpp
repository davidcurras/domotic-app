#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
#include "api.h"
#include "sensors.h"
#include "actuators.h"

void Api::Send404(EthernetClient client) {
  client.println("HTTP/1.1 404 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html><body>404</body></html>");
};

void Api::SendStatus(EthernetClient client, DHT dht) {
  // Send a standard http response header
  String data = "";
  data += Sensors::GetHumidity(dht);
  data += Sensors::GetTemperature(dht);
  data += Sensors::GetFlame();
  data += Sensors::GetGroundHumidity();
  data += Sensors::GetGasLevel();
  data += Actuators::GetIrrigationState();
  data += Actuators::GetLedsState();
  data += Actuators::GetFanState();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connnection: close");
  client.println();
  client.println("{");
  client.println(data);
  client.println("}");
};

void Api::URL(String httpReq, EthernetClient client, DHT dht) {
  Serial.println(httpReq);
  Serial.println(httpReq.substring(5, 10));
  if(httpReq.substring(5, 10) == "state") {
    Api::SendStatus(client, dht);
  } else if(httpReq.substring(5, 10) == "fan/0") {
    Actuators::SetFan(LOW);
  } else if(httpReq.substring(5, 10) == "fan/1") {
    Actuators::SetFan(HIGH);
  } else if(httpReq.substring(5, 16) == "firealarm/0") {
    Actuators::SetFireAlarm(LOW);
  } else if(httpReq.substring(5, 16) == "firealarm/1") {
    Actuators::SetFireAlarm(HIGH);
  } else if(httpReq.substring(5, 17) == "irrigation/0") {
    Actuators::SetGas(LOW);
  } else if(httpReq.substring(5, 17) == "irrigation/1") {
    Actuators::SetGas(HIGH);
  } else if(httpReq.substring(5, 12) == "light/0") {
    Actuators::SetLed(9, LOW);
  } else if(httpReq.substring(5, 12) == "light/1") {
    Actuators::SetLed(9, HIGH);
  }
};
