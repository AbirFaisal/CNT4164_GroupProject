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

void SensorServer::run()
{

    client = server.available();

    if (client)
    {
        Serial.println("Has client");
        String currentLine = "";
        while (client.connected())
        {
            Serial.println("Client is connected");
            if (client.available())
            {
                char c = client.read();
                Serial.println(c);
                if (c == '\n')
                {
                    // If the current line is blank, skip it.
                    if (currentLine.length() == 0)
                    {
                        client.println("HTTP/1.1 200 OK");
                        // client.println("Content-Type: application/json");
                        client.println("Content-Type: text/html");

                        client.println("Connection: close");
                        client.println();

                        client.println("<!DOCTYPE html>");
                        client.println("<html>");
                        client.println("<head>");
                        client.println("<title>ESP8266 Web Server</title>");
                        client.println("<style>");
                        client.println("body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }");
                        client.println("</style>");
                        client.println("</head>");
                        client.println("<body>");
                        client.println("<h1>Welcome to the ESP8266 Web Server</h1>");
                        client.println("<p>This is a simple webpage served from an ESP8266.</p>");
                        client.println("</body>");
                        client.println("</html>");


                        client.println();
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

