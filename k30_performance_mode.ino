#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress apIP(55, 55, 55, 55);

const char* networkName = "Arduino";  // Network name
const char* networkPassword = "";     // Network password, if any

ESP8266WebServer webServer(80);

void configureWiFi() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(networkName, networkPassword);
  webServer.on("/", displayPerformanceTable);
  webServer.onNotFound(handle404);
  webServer.begin();
}

void setupPerformanceMode() {
  configureWiFi();
}

void handlePerformance() {
  manageWiFiClient();
}

void manageWiFiClient() {
  webServer.handleClient();
}

void handle404() {
  String message = "Page Not Found \n\n";
  message += "URI: ";
  message += webServer.uri();
  message += "\nMethod: ";
  message += (webServer.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webServer.args();
  message += "\n";

  for (uint8_t i = 0; i < webServer.args(); i++) {
    message += " " + webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  webServer.send(404, "text/plain", message);
}

void displayPerformanceTable() {
  String html = "<html><head><title>Performance Overview</title></head><body>";
  html += "<center><h1>Performance Overview</h1>";
  html += "<table border='1'><tr><th>#</th><th>Time (ms)</th><th>Improved?</th></tr>";
  for (int i = 0; i < pressIndex; i++) {
    html += "<tr><td>" + String(i + 1) + "</td><td>" + String(pressDurations[i]) + "</td><td>" + (isImprove[i] ? "Yes" : "No") + "</td></tr>";
  }
  html += "</table></center></body></html>";
  webServer.send(200, "text/html", html);
}
