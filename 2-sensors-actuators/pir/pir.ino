#define LED_PIN 8
#define PIR_PIN 2

bool detectedStatus;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  pinMode(PIR_PIN, INPUT);
  Serial.begin(9600);

  // give the sensor some time to calibrate
  Serial.print("Calibrating sensor... ");
  delay(10000);
  Serial.println(" done");
  Serial.println("PIR SENSOR READY.");
  detectedStatus = false;
}

void loop()
{
  int current = digitalRead(PIR_PIN);
  if (current != detectedStatus)
  {
    detectedStatus = current;
    if (current)
    {
      Serial.println("detected!");
      digitalWrite(LED_PIN, HIGH);
    }
    else
    {
      Serial.println("no more detected.");
      digitalWrite(LED_PIN, LOW);
    }
  }
};
