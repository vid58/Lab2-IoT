#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>


#define SERVO 10
#define ECHO_PIN 12
#define TRIGGER_PIN 13


long duration, cm;
unsigned long closeTime = 0;
int pos = 0;
bool isOpen = false;

Servo s;
int cont=0;
char contrasena[]="1111";
char codigo[4];


LiquidCrystal lcd(2,3,4,5,6,7);

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {37, 36, 35, 34};
byte colPins[COLS] = {33, 32, 31, 30};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600);
  s.attach(SERVO);

  lcd.begin(16,2);
  // pinMode(RED_LED, OUTPUT);
  // pinMode(YELLOW_LED, OUTPUT);
  // pinMode(GREEN_LED, OUTPUT);
}

void loop()
{
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  pinMode(ECHO_PIN, INPUT);
  duration = pulseIn(ECHO_PIN, HIGH);
  
  cm = 0.01723 * duration;
  // Serial.print(cm);
  // Serial.println(" cm");

  if (cm <= 30 && !isOpen)
  {
    // Serial.println("close");
    lcd.setCursor(0,0);
    lcd.print("Password:");
    delay(1000);

    // lcd.setCursor(0,1);
    // lcd.println("Clave correcta.");
    // delay(1000);

    char customKey = customKeypad.getKey();
    Serial.println(customKey);

    if (customKey != NO_KEY){
      codigo[cont]=customKey;
      Serial.print(codigo[cont]);
      cont=cont+1;
      if (cont==4) {
        Serial.println("completed");
        if(codigo[0]==contrasena[0]&&codigo[1]==contrasena[1]&&codigo[2]==contrasena[2]&&codigo[3]==contrasena[3]){
          lcd.setCursor(0,1);
          lcd.print("Clave correcta.");
          s.write(90);
          delay(15);
          isOpen = true;
          closeTime = millis();
          // delay(1000);
          // digitalWrite(GREEN_LED, LOW);
        }
        else{
          lcd.setCursor(0,1);
          lcd.println("Clave incorrecta.");
          delay(1000);
          // digitalWrite(RED_LED,LOW);

        }
        cont=0;
      }
    }
  }
  else if ((cm > 30 && isOpen) || (isOpen && (millis() - closeTime >= 10000)))
  {
    s.write(0);
    delay(15);
    isOpen = false;
    lcd.clear();
  }
  delay(1000);
}