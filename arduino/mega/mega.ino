#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
#include "api.h"
#include "sensors.h"
#include "actuators.h"

#define DHT_PIN 3    
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x2B, 0x7B };
IPAddress ip(192, 168, 5, 6);
EthernetServer server(80);
// stores the received HTTP request
String httpReq;

void setup() {
  Serial.begin(9600); 
  dht.begin();
  Actuators::Init();
  Sensors::Init();
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println("server is at "+Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        // get a single character from the Ethernet port
        char httpChar = client.read();
        // build a string out of the received characters 
        httpReq += httpChar;      
        // answer first HTTP request immediately
        if (httpChar == '\n') {
          Api::URL(httpReq, client, dht);
          //delete string contents
          httpReq = "";
          client.stop();
        } // end if (httpChar == '\n')
      } // end if (client.available()
    } // end while (client.connected())
  } // end if (client)
  Sensors::WatchFlame();
  Sensors::WatchGasLevel();
  Sensors::WatchTemperature(dht);
}
