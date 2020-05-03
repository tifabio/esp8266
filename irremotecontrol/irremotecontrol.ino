#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <IRremoteESP8266.h>

const char* ssid = "...";
const char* password = "...";

const int tamanho = 68;
const int frequencia = 32;

IRsend irsend(D5);

ESP8266WebServer server(80);

void handleIndex() {
  String html = "<meta name='viewport' content='width=device-width, initial-scale=1'>"
                "<title>Controle Remoto</title>"
                "<style>"
                "table, button { width: 100%; }"
                "button { height: 100px; }"
                "td { padding: 20px; }"
                "</style>"
                "<table>"
                "<tr>"
                "<td><button onclick='f(`power`)'>Liga</button></td>"
                "<td><button onclick='f(`input`)'>Entrada</button></td>"
                "</tr>"
                "<tr>"
                "<td><button onclick='f(`volUp`)'>Volume +</button></td>"
                "<td><button onclick='f(`chnUp`)'>Canal +</button></td>"
                "</tr>"
                "<tr>"
                "<td><button onclick='f(`volDown`)'>Volume -</button></td>"
                "<td><button onclick='f(`chnDown`)'>Canal -</button></td>"
                "</tr>"
                "</table>"
                "<script>"
                "const f = u => fetch(u).then(r => console.log(r)).catch(e => console.error(e));"
                "</script>";
  server.send(200, "text/html", html);
}

void handlePower() {
  // Samsung Power On/Off
  unsigned int rawCmd[68]={4600,4350,700,1550,650,1550,650,1600,650,450,650,450,650,450,650,450,700,400,700,1550,650,1550,650,1600,650,450,650,450,650,450,700,450,650,450,650,450,650,1550,700,450,650,450,650,450,650,450,650,450,700,400,650,1600,650,450,650,1550,650,1600,650,1550,650,1550,700,1550,650,1550,650};
  irsend.sendRaw(rawCmd,tamanho,frequencia);
  server.send(200);
  delay(50);
}

void handleInput() {
  // Samsung Source/Input
  unsigned int rawCmd[68]={4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,400,700,400,700,1550,700,400,700,450,650,450,650,450,700,400,700,400,700,400,700,450,650,1550,700,1500,700,1550,650,1550,700,1500,700,1550,700,1500,700};
  irsend.sendRaw(rawCmd,tamanho,frequencia);
  server.send(200);
  delay(50);
}

void handleVolUp() {
  // Samsung Volume Up
  unsigned int rawCmd[68]={4600,4350,650,1550,700,1500,700,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,450,650,1550,700,1500,700,1550,700,1500,700,1550,650};
  irsend.sendRaw(rawCmd,tamanho,frequencia);
  server.send(200);
  delay(50);
}

void handleVolDown() {
  // Samsung Volume Down
  unsigned int rawCmd[68]={4600,4350,700,1550,650,1550,700,1500,700,450,650,450,700,400,700,400,700,400,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,450,650,1550,700,400,700,400,700,450,700,400,700,400,700,400,700,1550,700,400,700,1500,700,1500,700,1550,700,1500,700};
  irsend.sendRaw(rawCmd,tamanho,frequencia);
  server.send(200);
  delay(50);
}

void handleChnUp() {
  // Samsung Channel Up
  unsigned int rawCmd[68]={4600,4350,700,1500,700,1500,700,1550,700,450,650,400,700,450,650,450,700,400,700,1500,700,1550,650,1550,700,450,650,450,700,400,700,400,700,400,700,400,700,1550,700,400,700,400,700,1550,650,450,700,400,700,400,700,1550,650,450,650,1600,650,1550,650,450,700,1500,700,1500,700,1550,650};
  irsend.sendRaw(rawCmd,tamanho,frequencia);
  server.send(200);
  delay(50);
}

void handleChnDown() {
  // Samsung Channel Down
  unsigned int rawCmd[68]={4650,4300,700,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,650,450,650,1550,700,1500,700,1550,700,400,700,400,700,400,700,450,700,400,700,400,700,400,700,450,650,450,650,1550,700,400,700,450,650,400,700,1550,700,1500,700,1550,700,1500,700,400,700,1550,650,1550,700,1500,700};
  irsend.sendRaw(rawCmd,tamanho,frequencia);
  server.send(200);
  delay(50);
}


void setup(void){
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.on("/", handleIndex);
  server.on("/power", handlePower);
  server.on("/input", handleInput);
  server.on("/volUp", handleVolUp);
  server.on("/volDown", handleVolDown);
  server.on("/chnUp", handleChnUp);
  server.on("/chnDown", handleChnDown);
  server.begin();
  
  irsend.begin();
}

void loop(void){
  server.handleClient();
}
