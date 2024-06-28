#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecureBearSSL.h>

const char* ssid     = "XANHLA";
const char* password = "thuysy331111";
String serverName = "https://jsonplaceholder.typicode.com/todos/1";
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;
String title = "";
void setup() {
  Serial.begin(115200); // Bật Serial monitor để xem kết quả

  // Kết nối WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");

  // Tạo HTTPClient và gửi yêu cầu GET
  if (WiFi.status() == WL_CONNECTED) {
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure(); // Tạm thời bỏ qua xác minh chứng chỉ SSL

    HTTPClient https;

// https://jsonplaceholder.typicode.com/todos/1"
    if (https.begin(*client, "http://127.0.0.1:8888/device/device-code")) { // URL của API
      int httpCode = https.GET(); // Gửi yêu cầu GET
      Serial.println(httpCode);
      if (httpCode > 0) { // Kiểm tra mã trạng thái HTTP
        String payload = https.getString(); // Nhận nội dung phản hồi
        Serial.println(httpCode); // In mã trạng thái HTTP
        Serial.println(payload); // In nội dung phản hồi
        const size_t capacity = JSON_OBJECT_SIZE(4) + 60;
        DynamicJsonDocument doc(capacity);

        deserializeJson(doc, payload);
        title = doc["deviceCode"].as<String>(); // Lưu trường title vào biến

        Serial.println("Title: " + title); // In biến title ra Serial monitor
      } else {
        Serial.println("Error on HTTP request");
      }

      https.end(); // Đóng kết nối
    } else {
      Serial.println("Unable to connect");
    }
  }
}

void loop() {
  delay(1000);
}
