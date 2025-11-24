#pragma once

const char style_css[] PROGMEM = R"rawliteral(
body {
  font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, sans-serif;
  background-color: #f0f2f5;
  margin: 0;
  padding: 10px;
  color: #333;
}
.header {
  background-color: #fff;
  padding: 15px 20px;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0,0,0,0.1);
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
}
h1 {
  color: #0056b3;
  margin: 0;
  font-size: 1.5em;
}
.grid-container {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
  gap: 20px;
}
.card {
  background-color: #ffffff;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0,0,0,0.1);
  padding: 20px;
  text-align: center;
}
.card h2 {
  margin-top: 0;
  color: #0056b3;
}
.card-gate h3 {
  font-size: 2.5em;
  margin: 10px 0;
  font-weight: bold;
}
.gate-status-icon {
  font-size: 3em;
  line-height: 1;
  color: #ccc;
}
/* Water Gauge */
.gauge { width: 100%; max-width: 200px; margin: 10px auto; }
.gauge-body { width: 100%; height: 0; padding-bottom: 50%; background: #e0e0e0; position: relative; border-top-left-radius: 100px 200px; border-top-right-radius: 100px 200px; overflow: hidden; }
.gauge-fill { position: absolute; top: 100%; left: 0; width: inherit; height: 100%; background: #007bff; transform-origin: center top; transform: rotate(0deg); transition: transform 0.3s ease-out; }
.gauge-cover { width: 70%; height: 0; padding-bottom: 35%; background: #f0f2f5; position: absolute; top: 100%; left: 50%; transform: translate(-50%, -50%); border-radius: 50% 50% 0 0; font-size: 1.5em; font-weight: bold; color: #333; line-height: 70px; }
/* Status Dot */
.status-dot { width: 15px; height: 15px; border-radius: 50%; background-color: #e74c3c; /* Red by default */ }
.status-dot.connected { background-color: #2ecc71; /* Green when connected */ }
)rawliteral";