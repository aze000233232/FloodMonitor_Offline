# FloodMonitor Offline

An ESP32-based flood monitoring system with offline web interface for real-time water level monitoring and gate control.
Test commit

## Authors
- **Lian Cunanan**
- **Ardyan Perez**
- **Kenneth Manarang**
- **Aldrich Icat**
- **Charles Mirande**

## Features

- Real-time water level monitoring with visual gauges
- Gate status monitoring and control
- Responsive web interface
- Offline operation capability
- Card-based dashboard layout

## Hardware Requirements

- ESP32 Development Board
- Water level sensors (ultrasonic/pressure)
- Temperature sensors (optional)
- Servo motors for gate control (optional)
- Power supply

## Software Requirements

### Arduino IDE Setup

1. Install ESP32 board package:
   - File > Preferences
   - Add to Additional Board Manager URLs: `https://dl.espressif.com/dl/package_esp32_index.json`
   - Tools > Board > Boards Manager > Search "ESP32" > Install

2. Install required libraries (see libraries.txt for details):
   - ESPAsyncWebServer
   - AsyncTCP
   - ArduinoJson
   - OneWire (for sensors)
   - DallasTemperature (for temperature sensors)

### Installation

1. Clone this repository: `git clone https://github.com/Lian-Cunanan/FloodMonitor_Offline.git`
2. Open the main .ino file in Arduino IDE
3. Install libraries listed in `libraries.txt`
4. Configure your WiFi credentials
5. Upload to ESP32

## Usage

1. Power on the ESP32
2. Connect to the WiFi network
3. Open web browser and navigate to ESP32's IP address
4. Monitor water levels and gate status through the web interface

## File Structure

- `style_css.h` - CSS styles for web interface
- `libraries.txt` - Required Arduino libraries
- Main sketch file (to be created)

## License

MIT License
