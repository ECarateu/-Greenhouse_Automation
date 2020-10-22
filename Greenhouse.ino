#define HORA 3600000 //1 HOUR
#define MEIA 1800000 // HALF AN HOUR
#define MINUTO 60000 // 1 MINUTE
#define SEGUNDO 10000 // 10 SECONDS

int rele = 8;
int buzzer =7;


void setup() {
  
  pinMode(rele, OUTPUT);    //LOW ON RELAY  || HIGH OFF RELAY

}

void loop() {
  
  
//INITIAL BUZZER
  tone(buzzer,4978); 
  delay(500);
  noTone(buzzer);
  delay(200);
  
  //TIME WHEN THE SYSTEM IS OFF
  digitalWrite(rele, HIGH); 
  delay(HORA);

  //  BUZZER THAT ACTIVATES THE SYSTEM
  tone(buzzer,2960); 
  delay(900);
  noTone(buzzer);
  delay(200);

  //TIME WHEN THE SYSTEM IS ON
  digitalWrite(rele, LOW);
  delay(MINUTO);
  delay(MINUTO);
  delay(MINUTO);
  delay(MINUTO);
  delay(MINUTO);
  delay(MINUTO);
  delay(MINUTO);
  delay(MINUTO);
  delay(MINUTO);
  delay(200);
 

}
