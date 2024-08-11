#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress accessPointIP(55, 55, 55, 55);

const char* accessPointName = "Arduino_AP";  // Network name
const char* accessPointPassword = "";        // Network password, if any

ESP8266WebServer performanceWebServer(80);

void configureAccessPoint() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(accessPointIP, accessPointIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(accessPointName, accessPointPassword);
  performanceWebServer.on("/", servePerformanceDashboard);
  performanceWebServer.onNotFound(handlePageNotFound);
  performanceWebServer.begin();
}

void initializePerformanceServer() {
  configureAccessPoint();
}

void managePerformanceServer() {
  handleClientRequests();
}

void handleClientRequests() {
  performanceWebServer.handleClient();
}

void handlePageNotFound() {
  String message = "404 - Page Not Found

";
  message += "Requested URI: ";
  message += performanceWebServer.uri();
  message += "
HTTP Method: ";
  message += (performanceWebServer.method() == HTTP_GET) ? "GET" : "POST";
  message += "
Number of Arguments: ";
  message += performanceWebServer.args();
  message += "
";
  
  for (uint8_t i = 0; i < performanceWebServer.args(); i++) {
    message += " " + performanceWebServer.argName(i) + ": " + performanceWebServer.arg(i) + "
";
  }
  performanceWebServer.send(404, "text/plain", message);
}

void servePerformanceDashboard() {
  String htmlContent = "<html><head><title>Performance Dashboard</title></head><body>";
  htmlContent += "<center><h1>Performance Metrics</h1>";
  htmlContent += "<table border='1'><tr><th>Attempt</th><th>Duration (ms)</th><th>Improved?</th></tr>";
  for (int i = 0; i < logIndex; i++) {
    htmlContent += "<tr><td>" + String(i + 1) + "</td><td>" + String(pressDurationsLog[i]) + "</td><td>" + (improvementStatus[i] ? "Yes" : "No") + "</td></tr>";
  }
  htmlContent += "</table></center></body></html>";
  performanceWebServer.send(200, "text/html", htmlContent);
}
