#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials
const char* ssid = "ESP32_Network";
const char* password = "12345678";

// Create a web server on port 80
WebServer server(80);

// HTML page with embedded JS and CSS
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Meditación con Números de Grabovoi</title>
  <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@400;700&family=Merriweather:wght@400;700&display=swap" rel="stylesheet">
  <style>
    body {
      font-family: 'Roboto', sans-serif;
      background-color: #f0f8ff;
      background-size: cover;
      background-repeat: no-repeat;
      background-attachment: fixed;
      color: #333;
      text-align: center;
    }
    header {
      background-color: #36454f;
      padding: 20px;
    }
    h1, h2 {
      font-family: 'Merriweather', serif;
    }
    .formulario-meditacion {
      margin: 40px auto;
      padding: 20px;
      max-width: 400px;
      background-color: #3e4444;
      box-shadow: 0 0 10px rgba(0, 0, 0, 0.3);
    }
    #formulario-grabovoi select, #formulario-grabovoi button {
      width: 85%;
      padding: 10px;
      margin: 10px 0;
      border-radius: 5px;
      font-size: 16px;
    }
    #formulario-grabovoi select {
      background-color: #2f4f4f;
      color: #f5f5f5;
      border: 1px solid #ccc;
    }
    #formulario-grabovoi button {
      background-color: #556b2f;
      color: white;
      border: none;
      cursor: pointer;
    }
    #formulario-grabovoi button:hover {
      background-color: #6b8e23;
    }
    footer {
      margin-top: 30px;
      padding: 20px;
      background-color: #36454f;
      color: #c0c0c0;
    }
    .esfera-plateada {
      width: 300px;
      height: 300px;
      border-radius: 50%;
      background-color: #8c8c8c;
      background-image: radial-gradient(circle at 100px 100px, #ffffff, #8c8c8c);
      box-shadow: 0 10px 20px rgba(0, 0, 0, 0.5);
      margin: 40px auto;
      display: flex;
      justify-content: center;
      align-items: center;
    }
    #numero-en-esfera {
      font-size: 110px;
      color: black;
      animation: fadeIn 2s ease-in-out;
    }
    #tiempo-restante, #nombre-secuencia, #secuencia-completa {
      margin-top: 20px;
      font-size: 20px;
      color: #4f4f4f;
    }
    @keyframes fadeIn {
      from { opacity: 0; }
      to { opacity: 1; }
    }
  </style>
</head>
<body>
  <main>
    <section class="formulario-meditacion">
      <h2>Selecciona tu Secuencia Numérica</h2>
      <div id="formulario-grabovoi">
        <select id="secuencia-numerica" required>
          <option value="" disabled selected>Selecciona una secuencia...</option>
          <option value="123456789">123456789 - Amor Universal</option>
          <option value="987654321">987654321 - Prosperidad</option>
          <option value="741852963">741852963 - Salud Perfecta</option>
          <option value="369258147">369258147 - Paz Interior</option>
          <option value="112233445">112233445 - Protección</option>
          <option value="5197148">5197148 - Dinero Inesperado</option>
          <option value="9187948181">9187948181 - Restauración Completa de Órganos</option>
          <option value="212585212">212585212 - Armonía en Relaciones</option>
          <option value="14111963">14111963 - Sanación de la Tierra</option>
          <option value="14854232190">14854232190 - Éxito Profesional</option>
          <option value="5555555">5555555 - Limpieza Espiritual</option>
          <option value="894719546">894719546 - Protección Energética</option>
          <option value="132435465">132435465 - Creatividad</option>
          <option value="8888858888">8888858888 - Manifestación Rápida</option>
          <option value="317498317">317498317 - Energía Positiva</option>
          <option value="417894218">417894218 - Claridad Mental</option>
          <option value="917814218">917814218 - Motivación Constante</option>
          <option value="314159265">314159265 - Sabiduría Divina</option>
          <option value="284516589">284516589 - Conexión Espiritual</option>
          <option value="781203456">781203456 - Vitalidad Juvenil</option>
        </select>
        <button id="btnComenzar">Comenzar</button>
      </div>
    </section>

    <section id="pantalla-meditacion" style="display:none;">
      <div id="nombre-secuencia">Secuencia: </div>
      <div id="secuencia-completa">Números: </div>
      <div id="esfera" class="esfera-plateada">
        <span id="numero-en-esfera"></span>
      </div>
      <div id="tiempo-restante">Tiempo restante: 3:00</div>
    </section>
  </main>

  <script>
    document.getElementById("btnComenzar").addEventListener("click", function () {
      const selectElement = document.getElementById("secuencia-numerica");
      const secuencia = selectElement.value;
      if (!secuencia) return;

      const secuenciaNombre = selectElement.options[selectElement.selectedIndex].text.split('-')[1].trim();

      // Update view
      document.querySelector('.formulario-meditacion').style.display = 'none';
      document.getElementById('pantalla-meditacion').style.display = 'block';
      document.getElementById('nombre-secuencia').textContent = `Secuencia: ${secuenciaNombre}`;
      document.getElementById('secuencia-completa').textContent = `Números: ${secuencia}`;

      repetirSecuencia(secuencia, 3 * 60);
    });

    function repetirSecuencia(secuencia, duracionTotal) {
      const numeros = secuencia.split('');
      let indice = 0;
      let tiempoTranscurrido = 0;
      let mostrarNumero = true;

      const tiempoRestante = document.getElementById('tiempo-restante');
      const elementoNumero = document.getElementById('numero-en-esfera');

      const intervalo = setInterval(() => {
        const tiempoFaltante = duracionTotal - tiempoTranscurrido;
        const minutos = Math.floor(tiempoFaltante / 60);
        const segundos = tiempoFaltante % 60;
        tiempoRestante.textContent = `Tiempo restante: ${minutos}:${segundos.toString().padStart(2, '0')}`;

        if (tiempoTranscurrido >= duracionTotal) {
          clearInterval(intervalo);
          document.getElementById('pantalla-meditacion').style.display = 'none';
          document.querySelector('.formulario-meditacion').style.display = 'block';
        } else {
          if (mostrarNumero) {
            mostrarNumeroFuncion(numeros[indice]);
            indice = (indice + 1) % numeros.length;
            if (indice === 0) {
              mostrarNumero = false;
              setTimeout(() => mostrarNumero = true, 3000); // pause 3s
            }
          } else {
            elementoNumero.textContent = '';
          }
        }
        tiempoTranscurrido++;
      }, 1000);
    }

    function mostrarNumeroFuncion(num) {
      const elementoNumero = document.getElementById('numero-en-esfera');
      elementoNumero.classList.remove('animated');
      void elementoNumero.offsetWidth; // force reflow
      elementoNumero.classList.add('animated');
      elementoNumero.textContent = num;
    }
  </script>
</body>
</html>
)rawliteral";


// Handle root URL "/"
void handleRoot() {
  server.send(200, "text/html", htmlPage);
}

void setup() {
  Serial.begin(115200);

  // Start WiFi in Access Point mode
  WiFi.softAP(ssid, password);
  Serial.print("Access Point IP: ");
  Serial.println(WiFi.softAPIP());

  // Setup web server routes
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
