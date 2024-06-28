#ifndef MY_EEPROM_H
#define MY_EEPROM_H

#include <EEPROM.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include <string.h>

void saveJsonToEEPROM(const JsonDocument &doc, int startAddress);
void readJsonFromEEPROM(JsonDocument &doc, int startAddress, int maxLength);

#endif