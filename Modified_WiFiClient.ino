
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

const char* wifiNetworkName = "Network";

WiFiClient espClient;
int httpServerPort = 80;  // HTTP port

void establishWiFiConnection() {
  Serial.println("Initializing WiFi Connection...");
  WiFi.begin(wifiNetworkName); 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Attempting to Connect to WiFi...");
    delay(100);
  }
  Serial.println("Successfully Connected to WiFi Network");
}

int retrieveDataFromServer() {
  int retrievedValue = -1;
  HTTPClient httpClient;
  String getRequestUrl = "http://api.kits4.me/GEN/api.php?ACT=GET&DEV=1122&CH=1";
  httpClient.begin(espClient, getRequestUrl);
  int httpResponseCode = httpClient.GET();
  Serial.print("HTTP GET Response Code: ");
  Serial.println(httpResponseCode);
  if (httpResponseCode == HTTP_CODE_OK) {
    String serverResponse = httpClient.getString();
    Serial.print("Server Response: ");
    Serial.println(serverResponse);
    retrievedValue = serverResponse.toInt();
  } else {
    Serial.print("Error During HTTP GET Request: ");
    Serial.println(httpClient.errorToString(httpResponseCode).c_str());
  }
  httpClient.end();
  return retrievedValue;
}

void uploadDataToServer(int valueToUpload) {
  HTTPClient httpClient;
  String postRequestUrl = "http://api.kits4.me/GEN/api.php?ACT=SET&DEV=1122&CH=1&VAL=" + String(valueToUpload);
  httpClient.begin(espClient, postRequestUrl);
  int httpResponseCode = httpClient.GET();
  Serial.print("HTTP GET Response Code (Data Upload): ");
  Serial.println(httpResponseCode);
  httpClient.end();
}
