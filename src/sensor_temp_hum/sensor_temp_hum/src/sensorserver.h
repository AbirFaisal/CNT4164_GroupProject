/**
 * @file webserver.h
 * @brief Webserver that allows configation or returns data from sensor.
 * @author Abir Faisal <noreply@fau.edu>
 * @date 2020-03-04
 * @copyright Copyright (c) 2025 Florida Atlantic University/Abir Faisal
 * This software is released under the GNU GPLv3 License, see LICENSE.md
 */

#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include <WiFiManager.h>

#include <Arduino.h>


class SensorServer {

    public:

    WiFiServer server;

    WiFiClient client;
    WiFiManager wm;


    int PORTAL_TIMEOUT = 15;

    SensorServer();
    ~SensorServer();

    void setup();
    void run(float temperature, float humidity);


};


