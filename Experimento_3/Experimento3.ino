int sensorHumedad = A0;

#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

#define MOTOR 8
#define RED_LED 31
#define BLUE_LED 33
#define BUZZER 47


void setup() {
  Serial.begin(9600);
  pinMode(MOTOR, OUTPUT);
  pinMode(sensorHumedad,INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  lcd.begin(16,2);
}

void loop() {
  int humedad = analogRead(sensorHumedad);
  humedad = 1024 - humedad;
  Serial.print("Humedad:");
  Serial.println(humedad);

  lcd.setCursor(0,0);
  lcd.print("Humedad:");
  lcd.setCursor(0,1);
  lcd.print(humedad);
  
if(humedad < 205 && humedad >= 0){
  noTone(BUZZER);
	digitalWrite(MOTOR, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
	delay(1000);
}else if(humedad > 600){
  tone(BUZZER, 1000);
  digitalWrite(MOTOR, HIGH);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, HIGH);
  delay(1000);
} else {
  noTone(BUZZER);
  digitalWrite(MOTOR,HIGH);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);
  }
}