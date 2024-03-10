#define PIN_LEN 4
#define BOUNCING 500
#define NUM_BTN 4

#define BTN_1 4
#define BTN_2 5
#define BTN_3 6
#define BTN_4 7

#define LED_UNLOCKED 9
#define LED_LOCKED 10

int btns[NUM_BTN] = {BTN_1, BTN_2, BTN_3, BTN_4};

int pin[PIN_LEN];
int userPin[PIN_LEN];

bool pinSet = false;
int pinProgress = 0;

bool showResult = false;
bool unlocked = false;

void insertPin(int pin[PIN_LEN])
{
    pinProgress = 0;
    pinSet = false;
    Serial.println("Insert next pin part.");
    while (pinProgress < PIN_LEN)
    {
        for (int i = 0; i < NUM_BTN; i++)
        {
            if (digitalRead(btns[i]) == HIGH)
            {
                Serial.println("Got pin part.");
                pin[pinProgress] = btns[i];
                pinProgress++;
                Serial.println("Wait ...");
                delay(BOUNCING);

                if (pinProgress == PIN_LEN)
                {
                    Serial.println("Pin set");
                    pinSet = true;
                    break;
                }
                else
                {
                    Serial.println("Insert next pin part.");
                }
            }
        }
    }
    Serial.println("Pin set");
}

bool checkPin()
{
    for (int i = 0; i < NUM_BTN; i++)
    {
        if (pin[i] != userPin[i])
        {
            return false;
        }
    }
    return true;
}

void setup()
{
    Serial.begin(115200);
    Serial.flush();

    pinMode(BTN_1, INPUT);
    pinMode(BTN_2, INPUT);
    pinMode(BTN_3, INPUT);
    pinMode(BTN_4, INPUT);

    pinMode(LED_UNLOCKED, OUTPUT);
    pinMode(LED_LOCKED, OUTPUT);

    insertPin(pin);
}

void loop()
{
    if (showResult)
    {
        if (unlocked)
        {
            Serial.println("Correct pin");
            digitalWrite(LED_UNLOCKED, HIGH);
        }
        else
        {
            Serial.println("Wrong pin");
            digitalWrite(LED_LOCKED, HIGH);
        }
        delay(1000);
        digitalWrite(LED_LOCKED, LOW);
        digitalWrite(LED_UNLOCKED, LOW);
        showResult = false;
        unlocked = false;
    }
    else
    {
        Serial.println("Insert user pin.");
        insertPin(userPin);
        unlocked = checkPin();
        showResult = true;
    }
}