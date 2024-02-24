#include <LiquidCrystal.h>

int count = 0;

/* Pins: RS EN D4 D5 D6 D7 */
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup()
{
  lcd.begin(16, 2);
  lcd.print("Imola");
}

void loop()
{
  lcd.setCursor(0, 1);
  lcd.print(count);
  delay(1000);
  count++;
}