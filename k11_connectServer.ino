#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Network";

WiFiClient client;
int server_port = 80;  // http

void wifiClient_Setup() {
  Serial.println("wifiSetup");
  WiFi.begin(ssid); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("trying ...");
    delay(100);
  }
  Serial.println("Connected to network");
}

int GetData() {
  int ret = -1;
  HTTPClient http;
  String dataURL = "http://api.kits4.me/GEN/api.php?ACT=GET&DEV=1121&CH=1";
  http.begin(client, dataURL);
  int httpCode = http.GET();
  Serial.print("HTTP response code: ");
  Serial.println(httpCode);
  if (httpCode == HTTP_CODE_OK) {
    String Res = http.getString();
    Serial.print("Response: ");
    Serial.println(Res);
    ret = Res.toInt();
  } else {
    Serial.print("Error on HTTP request: ");
    Serial.println(http.errorToString(httpCode).c_str());
  }
  http.end();
  return ret;
}

void SendData(int val) {
  HTTPClient http;
  String dataURL = "http://api.kits4.me/GEN/api.php?ACT=SET&DEV=1121&CH=1&VAL=" + String(val);
  http.begin(client, dataURL);
  int httpCode = http.GET();
  Serial.print("HTTP response code (SendData): ");
  Serial.println(httpCode);
  http.end();
}
