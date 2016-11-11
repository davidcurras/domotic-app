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

String Api::GetStatus(EthernetClient client, DHT dht) {
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
  return data;
};

void Api::ProcessURL(String httpReq, EthernetClient client, DHT dht) {
  if(httpReq.substring(5, 10) == "fan/0") {
    Actuators::SetFan(LOW);
  } else if(httpReq.substring(5, 10) == "fan/1") {
    Actuators::SetFan(HIGH);
  } else if(httpReq.substring(5, 16) == "fireAlarm/0") {
    Actuators::SetFireAlarm(LOW);
  } else if(httpReq.substring(5, 16) == "fireAlarm/1") {
    Actuators::SetFireAlarm(HIGH);
  } else if(httpReq.substring(5, 17) == "irrigation/0") {
    Actuators::SetGas(LOW);
  } else if(httpReq.substring(5, 17) == "irrigation/1") {
    Actuators::SetGas(HIGH);
  } else if(httpReq.substring(5, 11) == "led2/0") {
    Actuators::SetLed(2, LOW);
  } else if(httpReq.substring(5, 11) == "led2/1") {
    Actuators::SetLed(2, HIGH);
  } else if(httpReq.substring(5, 11) == "led5/0") {
    Actuators::SetLed(5, LOW);
  } else if(httpReq.substring(5, 11) == "led5/1") {
    Actuators::SetLed(5, HIGH);
  } else if(httpReq.substring(5, 11) == "led6/0") {
    Actuators::SetLed(6, LOW);
  } else if(httpReq.substring(5, 11) == "led6/1") {
    Actuators::SetLed(6, HIGH);
  } else if(httpReq.substring(5, 11) == "led8/0") {
    Actuators::SetLed(8, LOW);
  } else if(httpReq.substring(5, 11) == "led8/1") {
    Actuators::SetLed(8, HIGH);
  } else if(httpReq.substring(5, 11) == "led9/0") {
    Actuators::SetLed(9, LOW);
  } else if(httpReq.substring(5, 11) == "led9/1") {
    Actuators::SetLed(9, HIGH);
  }
  String data = Api::GetStatus(client, dht);
  Serial.println(httpReq);
  Serial.println(data);
  Serial.println("=====================");
};
