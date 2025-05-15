#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "ESP32_Network";
const char* password = "12345678";

// Create a web server object
WebServer server(80);

// HTML content for the Grabovoi sequence webpage with styles
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Meditación con Números de Grabovoi</title>
  <style>
    body {
      font-family: 'Roboto', sans-serif;
      background-color: #f0f8ff;
      background-image: url('fondo 1.png');
      background-size: cover;
      background-repeat: no-repeat;
      background-attachment: fixed;
      color: #333;
      text-align: center;
    }
    .container {
      margin-top: 50px;
    }
    select, button {
      padding: 10px 20px;
      font-size: 16px;
      margin-top: 20px;
      cursor: pointer;
    }
    select {
      width: 250px;
    }
    button {
      background-color: #556b2f;
      color: white;
      border: none;
      border-radius: 5px;
    }
    button:hover {
      background-color: #6b8e23;
    }
    #output {
      margin-top: 20px;
      font-size: 18px;
      color: #4f4f4f;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>Meditación con Números de Grabovoi</h1>
    <select id="sequence">
      <option value="123456789">123456789 - Amor Universal</option>
      <option value="987654321">987654321 - Prosperidad</option>
      <option value="741852963">741852963 - Salud Perfecta</option>
      <option value="369258147">369258147 - Paz Interior</option>
      <option value="112233445">112233445 - Protección</option>
    </select>
    <br />
    <button onclick="startSequence()">Comenzar</button>
    <p id="output"></p>
    <script>
      function startSequence() {
        const sequence = document.getElementById('sequence').value;
        fetch('/start?sequence=' + sequence)
          .then(response => response.text())
          .then(data => document.getElementById('output').innerText = data);
      }
    </script>
  </div>
</body>
</html>
)rawliteral";

// Handle root URL "/"
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

// Handle starting the sequence
void handleStartSequence() {
  String sequence = server.arg("sequence");
  String response = "Secuencia seleccionada: " + sequence;
  server.send(200, "text/plain", response);

  // Add logic to process the sequence here
  // For example, display it on an OLED screen or perform another action
}

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.softAP(ssid, password);
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // Setup server routes
  server.on("/", handleRoot);
  server.on("/start", handleStartSequence);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
