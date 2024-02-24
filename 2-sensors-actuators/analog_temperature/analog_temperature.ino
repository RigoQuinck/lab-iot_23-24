#include <LiquidCrystal_I2C.h>

// should match the Beta Coefficient of the thermistor
const float BETA = 3950;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(A2);

  float celsius = 1 / (log(1 / (1023. / value - 1)) / BETA + 1.0 / 298.15) - 273.15;

  Serial.println(celsius);

  lcd.setCursor(0, 1);
  lcd.print(String("Value in C: ") + celsius);

  delay(1000);
}
