#include <SPI.h>
#include <Ethernet.h>
#include "api.h"
#include "actuators.h"

void Api::Send404(EthernetClient client) {
  client.println("HTTP/1.1 404 OK");
  client.println("Content-Type: text/html");
  client.println("Connnection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html><body>404</body></html>");
};

void Api::SendStatus(EthernetClient client, String data) {
  // Send a standard http response header
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: application/json");
  client.println("Connnection: close");
  client.println();
  client.println("{");
  client.println(data);
  client.println("}");
};

//get state of LED checkboxes from web page
void Api::SetLeds(String httpReq) {
  Serial.println(httpReq);
  for (byte i = 0; i < sizeof(Actuators::LEDS); i++) {
    String ledValue = String(Actuators::LEDS[i]) + '0';
    bool char9 = String(httpReq.charAt(9)) == ledValue;
    bool char16 = String(httpReq.charAt(16)) == ledValue;
    // if LED box is checked set led number to 1
    if (char9 && char16) { 
      Actuators::SetLed(i, HIGH);
    } else if (char9) {
      Actuators::SetLed(i, LOW);
    }
  }
};
