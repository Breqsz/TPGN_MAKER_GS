/*
 * Braco Robotico de Coleta de Amostras (Docking & Retrieval)
 * GS 2026 - Industria Espacial | FIAP ESW 4o Ano | PBML
 * Author: RODRIGO BRASILEIRO - RM98952
 *
 * 2x SG90 (9g) + LED de status. Controle pelo Monitor Serial (9600 baud):
 *   U / D -> sobe / desce a articulacao
 *   O / C -> abre / fecha a garra
 * LED aceso = garra fechada (segurando amostra).
 */

#include <Servo.h>

// Pinos
const uint8_t PIN_SERVO_ARM  = 9;    // articulacao (U/D)
const uint8_t PIN_SERVO_GRIP = 10;   // garra (O/C)
const uint8_t PIN_LED_STATUS = 7;    // LED via resistor 220 ohm

// Angulos (graus)
const int ARM_MIN   = 10;
const int ARM_MAX   = 170;
const int ARM_STEP  = 15;            // passo por comando U/D
const int ARM_START = 90;            // posicao inicial da articulacao
const int GRIP_OPEN  = 120;
const int GRIP_CLOSE = 30;
const int MOVE_DELAY = 15;           // ms por grau (movimento suave)

Servo servoArm;
Servo servoGrip;
int armAngle  = ARM_START;
int gripAngle = GRIP_OPEN;

// Move o servo grau a grau ate o alvo
void moveSmooth(Servo &s, int from, int to) {
  int step = (to >= from) ? 1 : -1;
  for (int a = from; a != to; a += step) { s.write(a); delay(MOVE_DELAY); }
  s.write(to);
}

// LED aceso quando a garra esta fechada (segurando amostra)
void updateLed() {
  digitalWrite(PIN_LED_STATUS, gripAngle == GRIP_CLOSE ? HIGH : LOW);
}

void printState() {
  Serial.print(F("[STATUS] Articulacao: ")); Serial.print(armAngle);
  Serial.print(F(" deg | Garra: "));
  Serial.println(gripAngle == GRIP_OPEN ? F("ABERTA") : F("FECHADA"));
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED_STATUS, OUTPUT);
  servoArm.attach(PIN_SERVO_ARM);
  servoGrip.attach(PIN_SERVO_GRIP);
  servoArm.write(armAngle);
  servoGrip.write(gripAngle);
  updateLed();
  Serial.println(F("Braco pronto. Comandos: U D O C"));
  printState();
}

void loop() {
  if (!Serial.available()) return;

  char cmd = Serial.read();
  if (cmd == '\n' || cmd == '\r' || cmd == ' ') return;   // ignora Enter/espaco
  cmd = toupper(cmd);

  switch (cmd) {
    case 'U': {                                   // sobe a articulacao
      int t = min(armAngle + ARM_STEP, ARM_MAX);
      moveSmooth(servoArm, armAngle, t); armAngle = t;
      Serial.println(F(">> UP"));
      break;
    }
    case 'D': {                                   // desce a articulacao
      int t = max(armAngle - ARM_STEP, ARM_MIN);
      moveSmooth(servoArm, armAngle, t); armAngle = t;
      Serial.println(F(">> DOWN"));
      break;
    }
    case 'O':                                     // abre a garra
      moveSmooth(servoGrip, gripAngle, GRIP_OPEN); gripAngle = GRIP_OPEN;
      Serial.println(F(">> OPEN"));
      break;
    case 'C':                                     // fecha a garra (captura)
      moveSmooth(servoGrip, gripAngle, GRIP_CLOSE); gripAngle = GRIP_CLOSE;
      Serial.println(F(">> CLOSE"));
      break;
    default:
      Serial.print(F("[ERRO] Comando invalido: ")); Serial.println(cmd);
      return;                                     // nao atualiza estado
  }

  updateLed();
  printState();
}
