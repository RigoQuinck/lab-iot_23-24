#define BUTTON_PIN 2

int count;

void setup()
{
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
  count = 0;
}

void loop()
{
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH)
  {
    count++;
    Serial.print("Pressed - count: ");
    Serial.println(count);
    delay(150);
  }
}
