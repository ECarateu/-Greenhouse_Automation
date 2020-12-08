#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>

#define buzzer 5

const char* ssid     = "XXXX";
const char* password = "XXXX";
const int  port = 8080;
DynamicJsonDocument API_RESPONSE(2048);
String status_da_bomba = "desligado";

// Busca hora
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br");


ESP8266WebServer server ( 80 );
HTTPClient http;

void ligaBomba(){
    Serial.println("Liga Bomba");
    tone(buzzer, 29600);
    status_da_bomba = "ligado";
    server.send(200, "text/plain", "BOMBA LIGADA"); 
}

void desligaBomba(){
   
    Serial.println("Desliga Bomba");
    noTone(buzzer);
    status_da_bomba = "desligado";
    server.send(200, "text/plain", "BOMBA DESLIGADA"); 
}


void iniciaRega() {
  // To-do 
  // Buscar o horário dinamicamente na API
  ligaBomba();
  delay(5000);
  desligaBomba();
}

void statusDaBomba(){
    server.send(200, "text/plain", String(status_da_bomba));
    
}

void verificaHorarioAcionamento(String horario) {

    for(int i = 0; i < API_RESPONSE.size(); i++) {
        Serial.println(horario);
        Serial.println(API_RESPONSE[i]["horario"].as<String>());
        if(horario == API_RESPONSE[i]["horario"].as<String>()) {
          Serial.println("BATEU MALUCO");
          iniciaRega();
        }
    }
}

IPAddress ip1 = ipaddr_addr("192.168.100.114");
IPAddress ip2 = ipaddr_addr("192.168.100.1");
IPAddress ip3 = ipaddr_addr("255.255.255.0");
IPAddress ip4 = ipaddr_addr( "8.8.8.8" );
IPAddress ip5 = ipaddr_addr( "8.8.4.4" );

void setup() {
  Serial.begin(115200);
  delay(10);

  // Checa o IP Fixo
  if (!WiFi.config(ip1, ip2, ip3, ip4, ip5)) {
    Serial.println("Falha ao configurar o WIFI");
  }


  timeClient.begin();
  timeClient.setTimeOffset(3* -3600);


  Serial.setDebugOutput(true);  
  Serial.println("Conectando no Wifi...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  
  Serial.println("");
  Serial.println("WIFI CONECTADO");
  Serial.println("IP: ");
  Serial.print(WiFi.localIP()); 
  
  server.on("/liga", ligaBomba);
  server.on("/desliga", desligaBomba);
  server.on("/status", statusDaBomba);
  server.begin();

  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);

  // Faz uma requisição para a API e verifica os horários do cliente atual

  if (WiFi.status() == WL_CONNECTED) {
  
    http.begin("http://ec2-15-228-60-66.sa-east-1.compute.amazonaws.com:3000/horario_horta"); 
    int httpCode = http.GET();
    
    if (httpCode > 0) {
    
      String payload = http.getString();
      Serial.println(payload);
      deserializeJson(API_RESPONSE, payload);
  
    }
    
    http.end();
  
  }
  
}


void loop() {
  
    timeClient.update();
    server.handleClient();
    String formattedTime = timeClient.getFormattedTime();
 

    verificaHorarioAcionamento(formattedTime);
    
    if(WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi ta morto !");
      Serial.println("RESETANDO...!");

      ESP.restart();
    } 
}