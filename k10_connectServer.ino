#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

const char* wifiNetwork = "Network";

WiFiClient wifiClient;
int httpPort = 80;  // http

void setupWiFiClient() {
  Serial.println("Setting up WiFi connection");
  WiFi.begin(wifiNetwork); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to connect...");
    delay(100);
  }
  Serial.println("Connected to WiFi network");
}

int fetchData() {
  int dataValue = -1;
  HTTPClient httpClient;
  String requestUrl = "http://api.kits4.me/GEN/api.php?ACT=GET&DEV=1122&CH=1";
  httpClient.begin(wifiClient, requestUrl);
  int httpResponseCode = httpClient.GET();
  Serial.print("HTTP response code: ");
  Serial.println(httpResponseCode);
  if (httpResponseCode == HTTP_CODE_OK) {
    String serverResponse = httpClient.getString();
    Serial.print("Server Response: ");
    Serial.println(serverResponse);
    dataValue = serverResponse.toInt();
  } else {
    Serial.print("HTTP request error: ");
    Serial.println(httpClient.errorToString(httpResponseCode).c_str());
  }
  httpClient.end();
  return dataValue;
}

void sendDataToServer(int value) {
  HTTPClient httpClient;
  String requestUrl = "http://api.kits4.me/GEN/api.php?ACT=SET&DEV=1122&CH=1&VAL=" + String(value);
  httpClient.begin(wifiClient, requestUrl);
  int httpResponseCode = httpClient.GET();
  Serial.print("HTTP response code (sendDataToServer): ");
  Serial.println(httpResponseCode);
  httpClient.end();
}
