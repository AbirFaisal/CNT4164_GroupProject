/**
 * @file webserver.cpp
 * @brief Webserver that allows configation or returns data from sensor.
 * @author Abir Faisal <noreply@fau.edu>
 * @date 2020-03-04
 * @copyright Copyright (c) 2025 Florida Atlantic University/Abir Faisal
 * This software is released under the GNU GPLv3 License, see LICENSE.md
 */

#include "sensorserver.h"

SensorServer::SensorServer() : server(80)
{
}

SensorServer::~SensorServer()
{
}

void SensorServer::setup()
{
    // Initialize WiFiManager
    wm.WiFiManagerInit();

    // Set a static IP configuration for the Access Point (AP) mode
    wm.setAPStaticIPConfig(IPAddress(192, 168, 0, 1), IPAddress(192, 168, 0, 1), IPAddress(255, 255, 255, 0));

    // Clears the settings stored in the EEPROM
    // wm.resetSettings();

    // Attempt to auto connect to a previously saved WiFi network using WiFiManager
    bool res = wm.autoConnect();

    // Check if the connection attempt was successful
    if (!res)
    {
        // If not successful, print an error message to the serial monitor
        Serial.println("Failed to connect");
        // Optionally, restart the ESP32/ESP8266 to try again (uncomment the line below)
        // ESP.restart();
    }
    else
    {
        // If connected successfully, print a success message to the serial monitor
        Serial.println("WiFi connecateda sucessafullay :)");
        server.begin(80);
    }
}

void SensorServer::run(float temperature, float humidity)
{

    client = server.available();

    char buffer[10];

    if (client)
    {
        Serial.println("Has client");

        String currentLine = "";

        while (client.connected())
        {
            // Serial.println("Client is connected");
            if (client.available())
            {
                char c = client.read();
                Serial.println(c);
                if (c == '\n')
                {
                    // If the current line is blank, skip it.
                    if (currentLine.length() == 0)
                    {
                        // Response Header
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: application/json");
                        client.println("Content-Type: text/html");
                        client.println("Connection: close");
                        client.println();

                        // Response
                        client.print("{\"id\": 1, \"temperature\": ");

                        dtostrf(temperature, 2, 3, buffer);
                        client.print(buffer);
                        
                        client.print(", \"humidity\": ");
                        dtostrf(humidity, 2, 3, buffer);
                        client.print(buffer);
                        client.print("}");                        

                        // End
                        client.println();
                        break;
                    }
                    // If you got a newline, then clear currentLine:
                    currentLine = "";
                }
                else if (c != '\r')
                {
                    // Otherwise the char is a normal char:
                    currentLine += c;
                }
            }
        }
    }

    client.stop();
    // Serial.println("Client Disconnected");
}

