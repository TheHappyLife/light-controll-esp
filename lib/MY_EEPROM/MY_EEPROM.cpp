#include "MY_EEPROM.h"

void saveJsonToEEPROM(const JsonDocument &doc, int startAddress)
{
  EEPROM.begin(512);

  // Serialize JSON thành chuỗi
  String json;
  serializeJson(doc, json);

  // Ghi chiều dài chuỗi JSON vào EEPROM
  int jsonLength = json.length();
  EEPROM.write(startAddress, jsonLength);

  // Ghi chuỗi JSON vào EEPROM
  for (int i = 0; i < jsonLength; i++)
  {
    EEPROM.write(startAddress + 1 + i, json[i]);
  }

  EEPROM.commit();
}

void readJsonFromEEPROM(JsonDocument &doc, int startAddress, int maxLength)
{
  EEPROM.begin(512);

  // Đọc chiều dài chuỗi JSON từ EEPROM
  int jsonLength = EEPROM.read(startAddress);
  if (jsonLength > maxLength)
  {
    Serial.println("JSON length exceeds buffer size");
    return;
  }

  // Đọc chuỗi JSON từ EEPROM
  char json[jsonLength + 1];
  for (int i = 0; i < jsonLength; i++)
  {
    json[i] = EEPROM.read(startAddress + 1 + i);
  }
  json[jsonLength] = '\0';

  // Deserialize JSON từ chuỗi
  deserializeJson(doc, json);
}