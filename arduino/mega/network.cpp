#include <SPI.h>
#include <Ethernet.h>
#include "network.h"
#include "api.h"

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x2B, 0x7B };
IPAddress ip(192, 168, 5, 6);
EthernetServer server(80);
// stores the received HTTP request
String httpReq;

void Network::Init() {
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("Server is at "+Ethernet.localIP());
};

void Network::Update() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        // get a single character from the Ethernet port
        // and build a string out of the received characters 
        char httpChar = client.read();
        httpReq += httpChar;      
        // answer first HTTP request immediately
        if (httpChar == '\n') {
          Api::ProcessURL(httpReq, client);
          //clear string contents
          httpReq = "";
          client.stop();
        }
      }
    }
  }
};
