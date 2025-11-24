/*
 * FLOOD MONITORING SYSTEM - OFFLINE WEB DASHBOARD
 *
 * This is the main project file.
 * All settings are in 'config.h'.
 * All webpage assets (HTML, CSS, JS) are in their own .h files.
 *
 * POWERING THE SERVO:
 * !! IMPORTANT !! Do NOT power the servo from the ESP32's 3.3V or 5V pin.
 * Power it from an external 5V power supply and share the GROUND (GND)
 * between the ESP32 and the external supply.
 */

// --- 1. Include Core Libraries ---
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <WebSocketsServer.h>
#include <DHT.h>
#include <ESP32Servo.h>

// --- 2. Include Your Project Files ---
#include "config.h"
#include "index_html.h"
#include "style_css.h"
#include "script_js.h"

// --- 3. Global Variables & Timers ---
unsigned long lastSensorRead = 0;
const long readInterval = 2000; // Read sensors every 2 seconds

// --- 4. Forward Declarations ---
// Tell the compiler these functions exist
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
void readSensorsAndBroadcast();

// --- 5. SETUP Function ---
void setup() {
  Serial.begin(115200);
  
  // --- Initialize Sensors & Actuators ---
  dht.begin();
  floodGate.attach(SERVO_PIN);
  floodGate.write(0); // Start with gate closed
  
  // Set ADC attenuation for analog sensors (0-3.3V range)
  analogSetPinAttenuation(WATER_LEVEL_PIN, ADC_11db);
  analogSetPinAttenuation(RAIN_SENSOR_PIN, ADC_11db);
  analogSetPinAttenuation(LDR_PIN, ADC_11db);

  // --- Start Wi-Fi Access Point ---
  Serial.print("Starting AP: ");
  Serial.println(ssid);
  WiFi.softAP(ssid, password);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP); // This is the address to type into your browser

  // --- Define Server Routes ---
  // Send the HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  
  // Send the CSS
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/css", style_css);
  });
  
  // Send the JavaScript
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/javascript", script_js);
  });

  // Start the server
  server.begin();
  
  // Start the WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent); // Set the event handler
}

// --- 6. MAIN LOOP Function ---
void loop() {
  webSocket.loop(); // Handle WebSocket clients

  unsigned long now = millis();
  if (now - lastSensorRead > readInterval) {
    lastSensorRead = now;
    readSensorsAndBroadcast();
  }
}

// --- 7. WebSocket Event Handler ---
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    
    // --- THIS IS THE CORRECTED LINE ---
    case WStype_CONNECTED: { 
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected from %s\n", num, ip.toString().c_str());
    }
      break;
      
    case WStype_TEXT:
      Serial.printf("[%u] got text: %s\n", num, payload);
      // You could add logic here to receive commands from the webpage
      break;
  }
}

// --- 8. Sensor & Broadcast Function ---
void readSensorsAndBroadcast() {
  // --- Read all sensors ---
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  // Analog readings are 0-4095
  int waterRaw = analogRead(WATER_LEVEL_PIN); 
  int rainRaw = analogRead(RAIN_SENSOR_PIN);
  int lightRaw = analogRead(LDR_PIN);
  
  // --- Process Data ---
  // Map water level to a 0-100% scale (adjust 0 and 4095 as needed)
  int waterPercent = map(waterRaw, 0, 4095, 0, 100);
  
  String rainStatus = (rainRaw < RAIN_THRESHOLD) ? "Raining" : "No Rain";

  // --- Floodgate Logic ---
  if (waterRaw > WATER_THRESHOLD) {
    gateAngle = 90; // Open gate
  } else {
    gateAngle = 0; // Close gate
  }
  floodGate.write(gateAngle);
  String gateStatus = (gateAngle == 90) ? "OPEN" : "CLOSED";
  
  // --- Create JSON data packet ---
  String jsonString = "{";
  jsonString += "\"temp\":" + String(temp, 1); // 1 decimal place
  jsonString += ", \"humidity\":" + String(humidity, 1);
  jsonString += ", \"water_raw\":" + String(waterRaw);
  jsonString += ", \"water_percent\":" + String(waterPercent);
  jsonString += ", \"rain_raw\":" + String(rainRaw);
  jsonString += ", \"rain_status\":\"" + rainStatus + "\"";
  jsonString += ", \"light_raw\":" + String(lightRaw);
  jsonString += ", \"gate_status\":\"" + gateStatus + "\"";
  jsonString += "}";
  
  Serial.println(jsonString); // For debugging
  
  // --- Send data to all connected clients ---
  webSocket.broadcastTXT(jsonString);
}