#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WifiConnect.h"
#include "Const.h"
#include "CommonFunction.h"
#include "MY_EEPROM.h"

ESP8266WebServer server(PORT);

void handleRoot()
{
  if (LittleFS.exists("/index.html"))
  {
    File file = LittleFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
  }
  else
  {
    server.send(404, "text/plain", "File not found");
  }
}

void setup()
{
  const String test = "NguyenDepTraiNe";

  if (!LittleFS.begin())
  {
    Serial.println("Failed to mount file system");
    return;
  }
  connectToWifi(SSID, PASSWORD);

  // Thiết lập web server
  server.on("/", handleRoot);
  server.serveStatic("/", LittleFS, "/");
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
}
