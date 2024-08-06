#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress apIP(55, 55, 55, 55);

const char* mySsid = "Z_Arduino";  // Network name
const char* pass = "";         // Network password, if any

ESP8266WebServer server(80);

void wifiSetup() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(mySsid, pass);
  server.on("/", performanceTable);
  server.onNotFound(handleNotFound);
  server.begin();
}

void performance_setup() {
  wifiSetup();
}

void performance_loop() {
  wifi_loop();
}

void wifi_loop() {
  server.handleClient();
}

void handleNotFound() {
  String message = "File Not Found \n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}
void performanceTable() {
  String html = "<html><head><title>Performance Table</title></head><body>";
  html += "<center><h1>Your Performance Table</h1>";
  html += "<table border='1'><tr><th>Index</th><th>Duration</th><th>Is Improve</th></tr>";
  for (int i = 0; i < 10; i++) {
    html += "<tr><td>" + String(i + 1) + "</td><td>" + String(pressDurations[i]) + "</td><td>" + (isImprove[i] ? "Yes" : "No") + "</td></tr>";
  }
  html += "</table></center></body></html>";
  server.send(200, "text/html", html);
}
