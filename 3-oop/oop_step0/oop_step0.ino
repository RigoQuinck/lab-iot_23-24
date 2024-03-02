class Counter
{

private:
  int count;

public:
  Counter(int value)
  {
    count = value;
  }

  ~Counter()
  {
    // destructor
  }

  void inc()
  {
    count++;
  }

  int getValue()
  {
    return count;
  }
};

int globalVar = 1;
Counter *c1;
Counter *c3;

void setup()
{
  int localVar = 3;
  Counter c(10);

  Serial.begin(9600);
  c1 = new Counter(20);
  c3 = new Counter(30);

  c = *c1;

  while (!Serial)
  {
  };

  Serial.println((unsigned long)&globalVar); // Printing the memory address of global variable 'globalVar'.
  Serial.println((unsigned long)&c);         // Printing the memory address of local object 'c'.
  Serial.println((unsigned long)&c1);        // Printing the memory address of pointer 'c1'.

  Serial.println((unsigned long)&localVar); // Printing the memory address of local variable 'localVar'.

  Serial.println((unsigned long)c1); // Printing the value (memory address) stored in pointer 'c1'.
  Serial.println((unsigned long)c3); // Printing the value (memory address) stored in pointer 'c3'.
}

void loop()
{
}
