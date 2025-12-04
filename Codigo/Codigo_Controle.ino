/*
 * Transmissor para o mini drone com PS2, NRF24L01 e HC-06
 * CE D9, CSN D10, MOSI D11, MISO D12, SCK D13
 * PS2: DAT D4, CMD D5, CLK D6, ATT D7
 * HC-06: RX D2, TX D3
 */

#include <PS2X_lib.h>
#include <RF24.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <nRF24L01.h>

struct RF24Data {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte AUX1;
  byte AUX2;
  byte switches;
};

PS2X ps2;
RF24 radio(9, 10);
SoftwareSerial bt(2, 3);

const uint64_t pipe = 0xE8E8F0F0E1LL;
const uint8_t deadband = 6;

RF24Data packet;
bool ps2Ready = false;

byte applyDeadband(byte v, bool invert) {
  // Centraliza valores próximos ao neutro (128) para evitar ruído e opcionalmente inverte o eixo
  int val = invert ? (255 - v) : v;
  if (abs(val - 128) < deadband)
    val = 128;
  return (byte)constrain(val, 0, 255);
}

void resetPacket() {
  packet.throttle = 255; // throttle baixo
  packet.yaw = 128;
  packet.pitch = 128;
  packet.roll = 128;
  packet.AUX1 = 0;
  packet.AUX2 = 0;
  packet.switches = 0;
}

byte readSwitches() {
  byte s = 0;
  if (ps2.Button(PSB_CROSS))
    s |= 1 << 0;
  if (ps2.Button(PSB_CIRCLE))
    s |= 1 << 1;
  if (ps2.Button(PSB_SQUARE))
    s |= 1 << 2;
  if (ps2.Button(PSB_TRIANGLE))
    s |= 1 << 3;
  if (ps2.Button(PSB_PAD_UP))
    s |= 1 << 4;
  if (ps2.Button(PSB_PAD_DOWN))
    s |= 1 << 5;
  return s;
}

void setupPS2() {
  int err = ps2.config_gamepad(6, 5, 7, 4, true, true);
  ps2Ready = (err == 0);
}

void setupRadio() {
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setChannel(76);
  radio.openWritingPipe(pipe);
  radio.stopListening();
}

void setup() {
  Serial.begin(115200);
  bt.begin(9600);
  resetPacket();
  setupPS2();
  setupRadio();
}

void updatePacketFromPad() {
  if (!ps2Ready) {
    resetPacket();
    return;
  }

  ps2.read_gamepad(false, 0);
  packet.throttle = applyDeadband(ps2.Analog(PSS_LY), false);
  packet.yaw = applyDeadband(ps2.Analog(PSS_RX), true); // vira ROLL no RX
  packet.pitch = applyDeadband(ps2.Analog(PSS_RY), true);
  packet.roll = applyDeadband(ps2.Analog(PSS_LX), true); // vira YAW no RX
  packet.AUX1 = ps2.Button(PSB_R1) ? 1 : 0;
  packet.AUX2 = ps2.Button(PSB_L1) ? 1 : 0;
  packet.switches = readSwitches();
}

void sendLine(const char* label, int value) {
  bt.print(label);
  bt.print(value);
  bt.print("\n");
}

void sendLineStr(const char* label, const char* value) {
  bt.print(label);
  bt.print(value);
  bt.print("\n");
}

// Converte throttle de 0-255 para percentual 0-100 para leituras mais intuitivas
int throttlePercent() {
  return map(packet.throttle, 0, 255, 0, 100);
}

// Calcula o deslocamento em torno do ponto neutro (128) para simular aceleração/giros
int axisOffsetFromCenter(byte v) {
  return (int)v - 128;
}

void sendDataToApp() {
  // Envia dados no formato esperado pelo app MIT App Inventor
  // Cada linha com prefixo seguido do valor

  // Status de conexão
  sendLineStr("CON:", ps2Ready ? "OK" : "FAIL");

  // Dados do controle (valores de 0-255)
  sendLine("PITCH:", packet.pitch);
  sendLine("ROLL:", packet.roll);
  sendLine("YAW:", packet.yaw);

  // Throttle (convertido para percentual 0-100 para melhor visualização)
  sendLine("BAT:", throttlePercent());

  // Tensão simulada (baseada no throttle, 0-100%)
  sendLine("VOLT:", throttlePercent());

  // Altura simulada (pode ser ajustada conforme necessário)
  sendLine("ALT:", 0);

  // Velocidade aproximada simulada
  sendLine("VLAPX:", throttlePercent());

  // Aceleração simulada (baseada nos valores do joystick)
  // AX, AY, AZ podem ser calculados a partir de pitch, roll, yaw
  sendLine("AX:", axisOffsetFromCenter(packet.pitch));
  sendLine("AY:", axisOffsetFromCenter(packet.roll));
  sendLine("AZ:", axisOffsetFromCenter(packet.yaw));

  // Giroscópio simulada (valores relativos ao centro 128)
  sendLine("GX:", axisOffsetFromCenter(packet.roll));
  sendLine("GY:", axisOffsetFromCenter(packet.pitch));
  sendLine("GZ:", axisOffsetFromCenter(packet.yaw));

  // Envia um delimitador final para indicar fim do pacote
  bt.print("\n");
}

void loop() {
  static unsigned long lastReport = 0;

  updatePacketFromPad();
  radio.write(&packet, sizeof(packet));

  unsigned long now = millis();
  if (now - lastReport > 500) {
    if (!ps2Ready) {
      setupPS2();
    }
    lastReport = now;

    // Debug no Serial
    Serial.print("PS2 ");
    Serial.print(ps2Ready ? "OK" : "FAIL");
    Serial.print(" | T:");
    Serial.print(packet.throttle);
    Serial.print(" Y:");
    Serial.print(packet.yaw);
    Serial.print(" P:");
    Serial.print(packet.pitch);
    Serial.print(" R:");
    Serial.print(packet.roll);
    Serial.print(" AUX:");
    Serial.print(packet.AUX1);
    Serial.print(packet.AUX2);
    Serial.print(" S:");
    Serial.println(packet.switches, BIN);

    // Envia dados formatados para o app via Bluetooth
    sendDataToApp();
  }
}
