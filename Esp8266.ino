#define HORA 3600000 //1 HORA
#define MEIA 1800000 // MEIA HORA
#define MINUTO 60000 // 1 MINUTO
#define SEGUNDO 10000 // 10 SEGUNDOS

#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define bomba D2
#define buzzer D1

// Replace with your network credentials
const char *ssid     = "Guilherme 401 Oi 2G";
const char *password = "32360236";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "a.st1.ntp.br");

//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};



void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

   pinMode(bomba, OUTPUT);//Define o pino como saida.
   digitalWrite(bomba, HIGH);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(3* -3600);
}

void loop() {
 
  timeClient.update();
  
  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);  

  if(formattedTime =="21:00:00"){
     
     tone(buzzer,2960); 
     delay(900);
     noTone(buzzer);
     delay(200);
     digitalWrite(bomba, LOW);//liga
     
    }
      

   if(formattedTime =="21:10:00"){
      tone(buzzer,4978); 
      delay(500);
      noTone(buzzer);
      delay(200);
     digitalWrite(bomba, HIGH);//desliga

    }

}
 
