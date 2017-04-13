#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "...";
const char* password = "...";

int bluePin = D1, redPin = D2, greenPin = D3;

ESP8266WebServer server(80);

void handleRoot() {
  String message = "<meta name='viewport' content='width=device-width, initial-scale=1'>"; 
  message += "<h2>ESP8266 Web Server</h2>";
  message += "<p><a href='/r'><button style='background-color:red;border:0;width:90px;height:90px;margin-right:20px'><b>&nbsp;</b></button></a>";
  message += "<a href='/g'><button style='background-color:green;border:0;width:90px;height:90px;margin-right:20px'><b>&nbsp;</b></button></a>";
  message += "<a href='/b'><button style='background-color:blue;border:0;width:90px;height:90px;margin-right:20px'><b>&nbsp;</b></button></a></p>";
  server.send(200, "text/html", message);
}

void handleR() {
  digitalWrite(greenPin, LOW);   
  digitalWrite(bluePin, LOW);  
  digitalWrite(redPin, HIGH);                          
  handleRoot();
}

void handleG() {
  digitalWrite(redPin, LOW);   
  digitalWrite(bluePin, LOW);  
  digitalWrite(greenPin, HIGH);   
  handleRoot();
}

void handleB() {
  digitalWrite(redPin, LOW);   
  digitalWrite(greenPin, LOW);  
  digitalWrite(bluePin, HIGH);  
  handleRoot();
}

void setup(void){
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", handleRoot);
  server.on("/r", handleR);
  server.on("/g", handleG);
  server.on("/b", handleB);

  server.begin();
}

void loop(void){
  server.handleClient();
}
