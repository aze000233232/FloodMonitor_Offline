#pragma once

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Flood Monitoring Dashboard</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <link rel="stylesheet" href="/style.css">
</head>
<body>
  <div class="header">
    <h1>IoT Flood Monitoring System</h1>
    <div class="status-dot" id="ws-status"></div>
  </div>

  <div class="grid-container">
    
    <div class="card card-water">
      <h2>Water Level</h2>
      <div class="gauge">
        <div class="gauge-body">
          <div class="gauge-fill" id="water-fill"></div>
          <div class="gauge-cover" id="water-value">0%</div>
        </div>
      </div>
      <p>Raw Value: <span id="water-raw">0</span></p>
    </div>

    <div class="card card-gate">
      <h2>Flood Gate Status</h2>
      <div class="gate-status-icon" id="gate-icon">!</div>
      <h3 id="gate-status">CLOSED</h3>
    </div>

    <div class="card card-rain">
      <h2>Rain Sensor</h2>
      <p id="rain-status">No Rain Detected</p>
      <p>Intensity: <span id="rain-value">0</span></p>
    </div>

    <div class="card card-env">
      <h2>Environment</h2>
      <p><strong>Temperature:</strong> <span id="temp-value">0</span> &deg;C</p>
      <p><strong>Humidity:</strong> <span id="humidity-value">0</span> %</p>
      <p><strong>Light:</strong> <span id="light-value">0</span></p>
    </div>

  </div>

  <script src="/script.js"></script>
</body>
</html>
)rawliteral";