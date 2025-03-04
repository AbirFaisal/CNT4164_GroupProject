/**
 * @file sensor.cpp
 * @brief Updates information for a connected sensor.
 * @author Abir Faisal <noreply@fau.edu>
 * @date 2020-02-06
 * @copyright Copyright (c) 2025 Florida Atlantic University/Abir Faisal
 * This software is released under the GNU GPLv3 License, see LICENSE.md
 */

#include "sensor.h"

Sensor::Sensor() {

}

Sensor::~Sensor() {

}

void Sensor::setup()
{
    // Wire.begin(SCA, SDL)
    Wire.begin(SDA_PIN, SCL_PIN);

    bool is_connected = AHT.begin();

    Serial.print("is_connected ");
    Serial.println(is_connected);

    // if (Serial.available())
    // {
        Serial.print("Init Sensor");
        Serial.print(DHT20_LIB_VERSION);
        
    // }
}

void  Sensor::run(float* temperature, float* humidity)
{
    #ifdef DEBUG
    Serial.print("Sensor Run State:");
    Serial.println(state);
    #endif

    switch (state)
    {
    case 0:
        // Request
        AHT.requestData();
        state++;
        break;
    case 1:
        // Read
        AHT.readData();
        state++;
        break;
    case 2:
        // Convert
        AHT.convert();

        // Update
        *temperature = getTemperature();
        *humidity = getHumidity();

        state++;
        break;
    default:
        state = 0;
        break;
    }
}

float  Sensor::getTemperature()
{
    return AHT.getTemperature();
}
float  Sensor::getHumidity()
{
    return AHT.getHumidity();
}
