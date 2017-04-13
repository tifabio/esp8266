#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "...";
const char* password = "...";

ESP8266WebServer server(80);

void handleRoot() {
  String message = "<meta name='viewport' content='width=device-width, initial-scale=1'>"; 
  message += "<h2>ESP8266 Web Server</h2>";
  message += "<p><a href='/ledon'><button><b>LED LIGAR</b></button></a></p>";
  message += "<p><a href='/ledoff'><button><b>LED DESLIGAR</b></button></a></p>";
  server.send(200, "text/html", message);
}

void handleLedOn() {
  digitalWrite(LED_BUILTIN, LOW);
  handleRoot();
}

void handleLedOff() {
  digitalWrite(LED_BUILTIN, HIGH);
  handleRoot();
}

void setup(void){
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", handleRoot);
  server.on("/ledon", handleLedOn);
  server.on("/ledoff", handleLedOff);

  server.begin();
}

void loop(void){
  server.handleClient();
}
