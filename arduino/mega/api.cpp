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

String Api::GetSensors() {
  String data = "";
  int gasLevel = Sensors::GetGasLevel();
  data += "\t\"gas\": \""+String(gasLevel)+"ppm\",\n";
  int gasType = Sensors::GetGasType();
  data += "\t\"gasState\": ";
  switch(gasType) { 
    case 0: data += "\"normal\",\n"; break; 
    case 1: data += "\"low-co2\",\n"; break; 
    case 2: 
    case 3: data += "\"high-co2\",\n"; break; 
    case 4:
    default: data += "\"high-butano\",\n"; break;
  }
  data += "\t\"fire\": ";
  data += Sensors::GetFlame() ? "true,\n" : "false,\n";
  float humidity = Sensors::GetHumidity();
  data += "\t\"humidity\": \""+String(humidity)+"%\",\n";
  float temperature = Sensors::GetTemperature();
  data += "\t\"temperature\": \""+String(temperature)+"C\",\n";
  float groundHumidity = Sensors::GetGroundHumidity();
  data += "\t\"groundHumidity\": \""+String(groundHumidity)+"%\",\n";
  return data;
};

String Api::GetActuators() {
  String data = "";
  data += "\t\"airConditioning\": ";
  data += Actuators::GetAutoFan() ? "true,\n" : "false,\n";
  data += "\t\"irrigation\": ";
  data += Actuators::GetIrrigation() ? "true,\n" : "false,\n";
  data += "\t\"inpureGas\": ";
  data += Actuators::GetGasLed() ? "true,\n" : "false,\n";
  data += "\t\"fireAlarm\": ";
  data += Actuators::GetFireLed() ? "true,\n" : "false,\n";
  data += "\t\"fan\": ";
  data += Actuators::GetFan() ? "true,\n" : "false,\n";
  data += "\t\"light\": ";
  data += Actuators::GetLight() ? "true,\n" : "false,\n";
  data += "\t\"led2\": ";
  data += Actuators::GetLed(2) ? "true,\n" : "false,\n";
  data += "\t\"led6\": ";
  data += Actuators::GetLed(6) ? "true,\n" : "false,\n";
  data += "\t\"led9\": ";
  data += Actuators::GetLed(9) ? "true\n" : "false\n";
  return data;
};

String Api::GetStatus(EthernetClient client) {
  // Send a standard http response header
  String data = "";
  data += Api::GetSensors();
  data += Api::GetActuators();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connnection: close");
  client.println();
  client.println("{");
  client.println(data);
  client.println("}");
  return data;
};

void Api::ProcessURL(String httpReq, EthernetClient client) {
  //FAN
  if(httpReq.substring(5, 10) == "fan/0") {
    Actuators::SetFan(LOW);
  } else if(httpReq.substring(5, 10) == "fan/1") {
    Actuators::SetFan(HIGH);
  }
  //LIGHT
  else if(httpReq.substring(5, 12) == "light/0") {
    Actuators::SetLight(LOW);
  } else if(httpReq.substring(5, 12) == "light/1") {
    Actuators::SetLight(HIGH);
  }
  //LED2
  else if(httpReq.substring(5, 11) == "led2/0") {
    Actuators::SetLed(2, LOW);
  } else if(httpReq.substring(5, 11) == "led2/1") {
    Actuators::SetLed(2, HIGH);
  }
  //LED6
  else if(httpReq.substring(5, 11) == "led6/0") {
    Actuators::SetLed(6, LOW);
  } else if(httpReq.substring(5, 11) == "led6/1") {
    Actuators::SetLed(6, HIGH);
  }
  //LED9
  else if(httpReq.substring(5, 11) == "led9/0") {
    Actuators::SetLed(9, LOW);
  } else if(httpReq.substring(5, 11) == "led9/1") {
    Actuators::SetLed(9, HIGH);
  }
  String data = Api::GetStatus(client);
  Serial.println(httpReq);
  Serial.println(data);
  Serial.println("=====================");
};
