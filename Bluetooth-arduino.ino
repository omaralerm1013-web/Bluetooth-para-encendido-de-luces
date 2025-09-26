#include <SoftwareSerial.h>

// Pines para SoftwareSerial (RX, TX) -> ojo: RX es donde Arduino lee (conectar TX del HC-05)
// Ajusta si quieres otros pines; en UNO evita los pines 0 y 1.
const uint8_t BT_RX = 10; // conecta aquí el TX del HC-05 (con divisor de tensión si el HC-05 RX es 3.3V)
const uint8_t BT_TX = 11; // conecta aquí el RX del HC-05

SoftwareSerial BT(BT_RX, BT_TX); // objeto SoftwareSerial para el HC-05

const uint8_t LED_PIN = 3; // define el pin del LED (puedes cambiarlo)

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  Serial.begin(9600);   // comunicación con la PC (Serial Monitor)
  BT.begin(9600);       // velocidad típica del HC-05
  Serial.println("Bluetooth listo, conecta tu celular!");
}

void loop() {
  // Datos desde Bluetooth -> mostrar en Serial y controlar LED
  if (BT.available()) {
    char c = BT.read();
    Serial.print("Recibido desde BT: ");
    Serial.println(c);

    if (c == '1') {
      digitalWrite(LED_PIN, HIGH);
      BT.println("LED encendido");
    }
    else if (c == '0') {
      digitalWrite(LED_PIN, LOW);
      BT.println("LED apagado");
    }
    else {
      BT.print("Eco: ");
      BT.println(c);
    }
  }

  // Datos desde Serial (PC) -> reenviar al módulo BT
  if (Serial.available()) {
    char d = Serial.read();
    BT.write(d); // reenvía byte a HC-05
  }
}
