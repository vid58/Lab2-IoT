#include <LiquidCrystal.h>
#include <Keypad.h>


#define ECHO_PIN 9
#define TRIGGER_PIN 10
#define GREEN_LED 11
#define YELLOW_LED 12
#define RED_LED 13

long duration, cm;

int cont=0;
char contrasena[]="1111";
char codigo[4];


LiquidCrystal lcd(7,6,5,4,3,2);

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = 
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {45, 43, 41, 39};
byte colPins[COLS] = {37, 35, 33, 31};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
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
  if (cm <= 30)
  {
    digitalWrite(YELLOW_LED, HIGH);
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
        if(codigo[0]==contrasena[0]&&codigo[1]==contrasena[1]&&codigo[2]==contrasena[2]&&codigo[3]==contrasena[3]){
          digitalWrite(GREEN_LED, HIGH);
          lcd.setCursor(0,1);
          lcd.print("Clave correcta.");
          delay(1000);
          digitalWrite(GREEN_LED, LOW);
        }
        else{
          digitalWrite(RED_LED, HIGH);
          lcd.setCursor(0,1);
          lcd.println("Clave incorrecta.");
          delay(1000);
          digitalWrite(RED_LED,LOW);

        }
        cont=0;
      }
    }

    lcd.clear();
  }
  else
  {
    digitalWrite(YELLOW_LED, LOW);
  }
  delay(100);
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}