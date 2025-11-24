#pragma once

// --- 1. Wi-Fi Settings ---
const char *ssid = "FloodMonitor_Network";
const char *password = "12345678";

// --- 2. Sensor Pins ---
#define WATER_LEVEL_PIN  34
#define RAIN_SENSOR_PIN  35
#define DHT_PIN          22
#define LDR_PIN          32
#define SERVO_PIN        13

// --- 3. Sensor Configuration ---
#define DHT_TYPE DHT22

// --- 4. Logic Thresholds (Adjust these!) ---
// Set the raw analog value (0-4095) from the water sensor that triggers the gate
#define WATER_THRESHOLD 3000 
// Set the raw analog value (0-4095) that indicates rain (lower = more sensitive)
#define RAIN_THRESHOLD  2000 

// --- 5. Global Variables ---
Servo floodGate;
int gateAngle = 0; // 0 = Closed, 90 = Open
DHT dht(DHT_PIN, DHT_TYPE);

AsyncWebServer server(80); // Server on port 80
WebSocketsServer webSocket(81); // WebSocket on port 81