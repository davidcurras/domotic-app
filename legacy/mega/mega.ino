#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"
#define DHTPIN 3    
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
//byte sensorpir = 7;
//byte led1 = 13; 
int fan = 7; // prende ventilador cuando la temp es superior a 27c
int s_analogica_mq135=0; // sensor de calidad del aire
int aire =20;
int CO2=11;
int gas=15;
int FLAME = 1;  //DETECTOR DE LLAMA              
int LED10= 13;    //LED O SPEASKER
int LED1 = 25;
int hum = 0;
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x2B, 0x7B };    // MAC address



IPAddress ip(192,168,5, 6);                               // IP address

EthernetServer server(80);

char char_in = 0;    // used to store a character from the Ethernet port
String HTTP_req;     // stores the received HTTP request

const byte LED_pins[] = { 2, 9, 6, 5, 8};          // Arduino pins usados para encender
byte LED[sizeof(LED_pins)] = {0};        // the state of each LED

void setup()
{
    
    dht.begin();
    //pinMode(sensorpir,INPUT);
    pinMode(aire,OUTPUT);
    pinMode(CO2,OUTPUT);
    pinMode(gas,OUTPUT);
    pinMode(7,OUTPUT);//configuracion del pin 12 ventilador
    digitalWrite(aire,LOW);
    digitalWrite(CO2,LOW);
    digitalWrite(gas,LOW);   
    pinMode(LED10, OUTPUT);// LED O SPEAKER DETECTOR LLAMA
    pinMode(FLAME, INPUT); // SENSOR LLAMA
    pinMode(12, INPUT);
    Ethernet.begin(mac, ip);
    server.begin();
    
    // set up the LED pins as outputs
    for (byte index = 0; index < sizeof(LED_pins); index++) {
        pinMode(LED_pins[index], OUTPUT);
    }
}

void loop()
{
    
    //digitalWrite(LED1, digitalRead(FLAME)); 
        
    EthernetClient client = server.available();


    if (client) {
        while (client.connected()) {
            if (client.available()) {
                char_in = client.read();  // get a single character from the Ethernet port
                HTTP_req += char_in;      // build a string out of the received characters
   
                // answer first HTTP request immediately
                if (char_in == '\n') {
                    // respond to HTTP request
                                      
                    client.println("HTTP/1.1 200 OK");
                    //client.println("Content-Type: text/html");
                    client.println();
                  client.println("<html lang='es'>");
          client.println("<head>");
          client.println("<center>"); 
          client.println("<meta charset='UTF-8'>");
          client.println("<title>");
          
          client.println("</title>");
          client.println("<link");
          client.println("href='http://fonts.googleapis.com/css?family=Roboto:300|Playfair+Display:400'");
          client.println("rel='stylesheet'");
          client.println("type='text/css'/>");
          //client.println("href='http://static.tumblr.com/pjglohe/2qinf00ga/estilos.min.css'>");
          client.println("</head>");
          client.println("<body>");
          client.println("<div class='page-wrap'>");
          client.println("<header class='header'>");
          client.println("<h1>");
          client.println("EasyHome");
          client.println("</h1>");
          client.println("<div class='educachip'>");
          client.println("<span>Realizado por </span>");
          client.println("Bosio, Luis - Debuchi, Axel");
          client.println("</a>");
          client.println("</div>");
          client.println("</header>"); 
          client.println("<section class='content-wrap'>");
          client.println("<div class='device'>");
          client.println("<div class='device-name'>");
          client.println("</center>"); 
          client.print("</div>");    
          // sensor Temperatura y Humedad
          float h = dht.readHumidity();
          float t = dht.readTemperature();    
           client.print("  --Humedad: "); 
        client.print(h);
        client.print(" %\t--");
        client.print("  Temperatura:   "); 
        client.print(t);
        client.println(" *C --");         
        client.println();
        // Prende le aire cuando llega tº a 25º
    if (t < 25)
  {
  digitalWrite(7, LOW);
  
  }else
  {
  digitalWrite(7,HIGH);
  
  client.println("--Aire Encendido--");
  }
   //Mide la calidad del aire
  s_analogica_mq135 = analogRead(0);       
   client.println("  Calidad del Aire:  ");
   client.println(s_analogica_mq135, DEC);
    client.println(" ppm");
  delay(250); 
  //aire 
  if(s_analogica_mq135<=100)
  {
  client.println(" Normal--");
  digitalWrite(aire,LOW);
  digitalWrite(CO2,LOW);
  digitalWrite(gas,LOW);
  delay(50);
  }


  if(s_analogica_mq135>=101 && s_analogica_mq135<=199)
  //aire con dioxido humano
  {
  client.println("Contiene poco de CO2--");
  digitalWrite(aire,HIGH);
  digitalWrite(CO2,LOW);
  digitalWrite(gas,LOW);
  delay(50);
  }
  //dioxido de carbono
  if(s_analogica_mq135>=200 && s_analogica_mq135<=350)
  {
  client.println(" Contiene Dioxido de Carbono CO2--");
  digitalWrite(aire,LOW);
  digitalWrite(CO2,HIGH);
  digitalWrite(gas,LOW);
  delay(50);
  }
  //gas propano y butano
  if(s_analogica_mq135>=400)
  {
  client.println();
  client.println(" Contiene Butano--  ");
  digitalWrite(aire,LOW);
  digitalWrite(CO2,LOW);
  digitalWrite(LED10,HIGH);
  delay(50);
  }

  // Detectecccion de fuego
  if(digitalRead(FLAME)==HIGH)
  {
    digitalWrite(LED10,HIGH);
    client.println(" -- Se Detecto Fuego--"); 
    }
   else
  {
    digitalWrite(LED10,LOW);
   }
 
 
 if(digitalRead(12)==HIGH)
    {
    client.println(" --Se encendio Riego-- ");
    }
 
  // put your main code here, to run repeatedly:
    int val = analogRead(A1);
    hum = (100 * val)/1024;
    client.print("  Humedad de Suelo  ");
    client.println(hum);
    client.println(" % ");  
    
                  
                    CheckLEDs();              // get state of LED checkboxes from web page
                    DisplayLEDs(&client);     // display checkboxes on web & write to LEDs
                    HTTP_req = "";      // delete string contents
                    client.stop();
                } // end if (char_in == '\n')
            } // end if (client.available()
        } // end while (client.connected())
    } // end if (client)
}

// get the state of the LED checkboxes from the HTTP request
void CheckLEDs()
      {
    for (byte led_num = 0; led_num < sizeof(LED_pins); led_num++) {
        if ((HTTP_req.charAt(9) == (LED_pins[led_num] + '0')) &&
                    (HTTP_req.charAt(16) == (LED_pins[led_num] + '0'))) {  // LED box is checked
            LED[led_num] = 1;
        }
        else if (HTTP_req.charAt(9) == (LED_pins[led_num] + '0')) {        // LED box is unchecked
            LED[led_num] = 0;
        }
    }
}

// write the HTML that includes the state of the LED checkboxes for displaying on the web browser
void DisplayLEDs(Client *client)
{
    // some CSS in the HTML to change colours and position of the box containing the LED checkboxes
    client->print("<div style=\"background:white; color:green; position: absolute; margin:20px; border: grey solid 2px; padding:0 10px 4px 10px;\">");
    client->print("<h1 style=\"font: normal 20px/150% Verdana, Arial, Sans-serif;\">Dispositivos de la Casa</h1>");
    // send each LED checkbox in turn
    for (byte led_num = 0; led_num < sizeof(LED_pins); led_num++) {
        // use hidden checkbox so that unchecking a checkbox sends a value to the Arduino
        // if only a normal checkbox is used, nothing is sent when it is unchecked
        // both hidden and normal checkboxes are produced here for each LED
        client->print("<form> <input type=\"hidden\" name=\"LED");
        client->print(LED_pins[led_num], DEC);
        client->print("\" value=\"0\"> <input type=\"checkbox\" name=\"LED");
        client->print(LED_pins[led_num], DEC);
        client->print("\" value=\"");
        client->print(LED_pins[led_num], DEC);
        client->print("\"");
        //write to the LED connected to the Arduino board
        if (LED[led_num]) {
            client->print(" checked ");             // part of HTML if checkbox is to be displayed checked
            digitalWrite(LED_pins[led_num], HIGH);  // switch LED on
        }
        else {
            digitalWrite(LED_pins[led_num], LOW);  // switch LED off
        }
        client->print(" onclick=\"submit();\">LED");
        client->print(LED_pins[led_num], DEC);
        client->print(" </form>");                 // end of HTML for 1 LED's form
        
    
    }
//cambiar numero en funcion de lo que se desee

       
    // end of box containing LEDs
}
