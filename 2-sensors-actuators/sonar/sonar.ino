const int trigPin = 8;
const int echoPin = 7;

/* Supposing to run this test
   in an environment with 20 °C
  ì https://en.wikipedia.org/wiki/Speed_of_sound
   */

const float speed = 343.21; // Speed estiation at 20 celsius

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float getDistance()
{
  /* Triggering stage: sending the impulse */

  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  /* Receiving the echo */

  float tUS = pulseIn(echoPin, HIGH);
  float t = tUS / 1000.0 / 1000.0 / 2;
  float d = t * speed;
  return d;
}

void loop()
{
  float d = getDistance();
  Serial.println(d);
  delay(50);
}
