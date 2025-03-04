/**
 * @file sensor.h
 * @brief Updates information for a connected sensor.
 * @author Abir Faisal <noreply@fau.edu>
 * @date 2020-02-06
 * @copyright Copyright (c) 2025 Florida Atlantic University/Abir Faisal
 * This software is released under the GNU GPLv3 License, see LICENSE.md
 */

#define SDA_PIN 0
#define SCL_PIN 2

#include "DHT20.h"

class Sensor {

    public:

    int read_rate = 5000; // ms

    DHT20 AHT;

    uint8_t state = 0;

    Sensor();
    ~Sensor();


    void setup();
    void run(float* t, float* h);
    float getTemperature();
    float getHumidity();
    


};


