#include<UltraDistSensor.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
UltraDistSensor ss;
int piezo = 8;


class Senzor
{
  float distanta;
public:
  void show()
  {
    distanta=ss.distanceInCm();
    lcd.setCursor(0,0);
    lcd.print("Distanta: ");
    lcd.print(this->distanta);
    delay(1000);
  }
  float getDist()
  {
    return this->distanta;
  }
};

void setup()
{
  lcd.init();             
  lcd.backlight();
  Serial.begin(9600);
  ss.attach(12,13);
}

void loop()
{
  Senzor s;
  s.show();
  if (s.getDist()<4)
  {
    tone(piezo,700,500);
    delay(0);
  }
  else if (s.getDist()<10)
  {
    tone(piezo,700,500);
    delay(250);
  }
  else if (s.getDist()<15)
  {
    tone(piezo,700,500);
    delay(700);
  }
  else if (s.getDist()<20)
  {
    tone(piezo,700,500);
    delay(1300);
  }
  else noTone(piezo);
}
