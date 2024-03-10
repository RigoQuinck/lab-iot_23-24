#define LED_NUM 3
#define LED_1 7
#define LED_2 8
#define LED_3 9

#define BTN 10

int leds[LED_NUM] = {LED_1, LED_2, LED_3};

long ledOn;
bool isLedOn = false;

void setup()
{
    // if analog input pin 0 is unconnected, random analog
    // noise will cause the call to randomSeed() to generate
    // different seed numbers each time the sketch runs.
    // randomSeed() will then shuffle the random function.
    randomSeed(analogRead(0));

    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    pinMode(BTN, INPUT);
}

void loop()
{
    if (!isLedOn)
    {
        delay(1000);
        ledOn = random(LED_NUM);
        digitalWrite(leds[ledOn], HIGH);
        isLedOn = true;
    }
    else
    {
        if (digitalRead(BTN))
        {
            digitalWrite(leds[ledOn], LOW);
            isLedOn = false;
        }
    }
}