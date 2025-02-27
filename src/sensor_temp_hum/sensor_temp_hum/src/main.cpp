// ESP8266 Temperature and Humidity Sensor

/*
  ESP8266 Pinout

  RX/GPIO3 1 2 3.3v VCC
  GPIO0    3 4 RESET
  GPIO2    5 6 ENABLE
  GND      7 8 GPIO1/TX/LED

*/

#include <Arduino.h>

class Main
{
public:
  Main()
  {
  }

  void blink()
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
};

// put function declarations here:
int myFunction(int, int);

void setup()
{
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
}

void loop()
{
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}