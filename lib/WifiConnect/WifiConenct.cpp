#include "WifiConnect.h"
#include <Arduino.h>

void connectToWifi(const String ssid, const String password)
{
    IPAddress local_IP(192, 168, 1, 184); // Set your desired IP address
    IPAddress gateway(192, 168, 1, 1);    // Set your network gateway
    IPAddress subnet(255, 255, 255, 0);   // Set your network subnet mask
    IPAddress dns(8, 8, 8, 8);            // Optional: Set your DNS server

    // Set static IP address
    if (!WiFi.config(local_IP, gateway, subnet, dns)) {
      Serial.println("STA Failed to configure");
    }

    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi: " + ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected.");
    Serial.println("http://" + WiFi.localIP().toString());
}