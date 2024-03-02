#define BUTTON_PIN 2

const unsigned long bounce_delay = 150;
int count;
boolean buttonHold = false;
unsigned long tsHold = 0;

void setup()
{
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
  count = 0;
  pinMode(13, OUTPUT);
}

void loop()
{
  unsigned long ts = millis();
  if (ts - tsHold >= bounce_delay)
  {
    buttonHold = false;
  }

  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH && !buttonHold)
  {
    count++;
    Serial.print("Pressed - count: ");
    Serial.println(count);
    // delay(150);
    // buttonState = LOW;
    buttonHold = true;
    tsHold = millis();
  }

  if (count % 2)
  {
    digitalWrite(13, HIGH);
  }
  else
  {
    digitalWrite(13, LOW);
  }
}
