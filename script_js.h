#pragma once

const char script_js[] PROGMEM = R"rawliteral(
// Establish WebSocket connection
var gateway = `ws://${window.location.hostname}:81/`;
var websocket;
var wsStatus = document.getElementById('ws-status');

// Init WebSocket
function initWebSocket() {
  console.log('Trying to open a WebSocket connection...');
  websocket = new WebSocket(gateway);
  
  websocket.onopen  = onOpen;
  websocket.onclose = onClose;
  websocket.onmessage = onMessage;
}

// Connection opened
function onOpen(event) {
  console.log('Connection opened');
  wsStatus.classList.add('connected');
}

// Connection closed
function onClose(event) {
  console.log('Connection closed');
  wsStatus.classList.remove('connected');
  setTimeout(initWebSocket, 2000); // Try to reconnect
}

// Message received from server
function onMessage(event) {
  console.log(event.data);
  var data = JSON.parse(event.data);
  
  // 1. Update Water Level
  var waterPercent = data.water_percent;
  document.getElementById('water-value').innerHTML = waterPercent + '%';
  document.getElementById('water-raw').innerHTML = data.water_raw;
  // Rotate gauge (0% = 0deg, 100% = 180deg)
  var waterAngle = (waterPercent / 100) * 180; 
  document.getElementById('water-fill').style.transform = `rotate(${waterAngle}deg)`;
  
  // 2. Update Gate Status
  var gateStatus = document.getElementById('gate-status');
  var gateIcon = document.getElementById('gate-icon');
  if (data.gate_status == "OPEN") {
    gateStatus.innerHTML = "OPEN";
    gateStatus.style.color = "#2ecc71";
    gateIcon.style.color = "#2ecc71";
    gateIcon.innerHTML = "&#10003;"; // Checkmark
  } else {
    gateStatus.innerHTML = "CLOSED";
    gateStatus.style.color = "#e74c3c";
    gateIcon.style.color = "#e74c3c";
    gateIcon.innerHTML = "&#10005;"; // X mark
  }

  // 3. Update Rain Sensor
  document.getElementById('rain-value').innerHTML = data.rain_raw;
  document.getElementById('rain-status').innerHTML = data.rain_status;

  // 4. Update Environment
  document.getElementById('temp-value').innerHTML = data.temp;
  document.getElementById('humidity-value').innerHTML = data.humidity;
  document.getElementById('light-value').innerHTML = data.light_raw;
}

// Start WebSocket connection when page loads
window.addEventListener('load', initWebSocket);
)rawliteral";