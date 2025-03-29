/**
 * @file main.cpp
 * @brief IoT and Sensor Networks project
 * @author Abir Faisal <noreply@fau.edu>
 * @date 2025-02-06
 * @copyright Copyright (c) 2025 Florida Atlantic University/Abir Faisal
 * This software is released under the GNU GPLv3 License, see LICENSE.md
 */

/*
  ESP8266 Pinout

  RX/GPIO3     1 2  3.3v VCC
  GPIO0/SDA    3 4  RESET
  GPIO2/SCL    5 6  ENABLE
  GND          7 8  GPIO1/TX/LED

*/

/*
  Behaviors

  Attempt to find AP
  Attempt to connect

  if success, respond with JSON
  else 
    create AP
    allow connection
    present setup page

*/


#define DEBUG 1

#define DEFAULT_SSID ''
#define DEFAULT_WPA2 ''

#define SDA_PIN 0
#define SCL_PIN 2

#include <Arduino.h>
#include "sensor.h"
#include "sensorserver.h"

class Main
{
  public:
  // Services
  Sensor sensor0;
  SensorServer sensorServer0;

  // shared variables
  float temperature = 0.0;
  float humidity = 0.0;

  Main()
  {
  }

  void setup(){
    sensor0.setup();
    sensorServer0.setup();
  }

  void run() {
    // Serial.println("Running...");

    // run and update
    sensor0.run(&temperature, &humidity);
    
    sensorServer0.run(temperature, humidity);

    // print status
    // Serial.print("temperature ");
    // Serial.println(temperature);

    // Serial.print("humidity ");
    // Serial.println(humidity);

    // delay(500);
  }

  void blink()
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
  }
};


Main prog;


void setup()
{
  Serial.begin(115200);
  delay(1000); // wait for serial connection to be established
  Serial.println("Starting...");

  // Wire.begin(SDA_PIN, SCL_PIN); // Initialize the I2C bus with defined SDA and SCL pins

  prog.setup();  
}

void loop()
{
  prog.run();
}
