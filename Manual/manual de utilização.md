
### Instruções de utilização

## 1. Preparação e Configuração do Hardware
# 1.1. Montagem Final

Antes da utilização, certifique-se de que:
- todos os motores estão firmemente fixados à estrutura impressa em 3D;
- as hélices estão instaladas na orientação correta (CW/CCW);
- o módulo NRF24L01 receptor está devidamente conectado e com alimentação estável;
- a bateria está fixada e conectada ao sistema;
- não há fios soltos que possam tocar nas hélices.

# 1.2. Calibração Inicial

Antes do primeiro voo:
- Conecte o drone ao computador usando o adaptador FTDI.
- Abra o firmware MultiWii na IDE Arduino.

Execute:
- Calibração do acelerômetro
- Verifique no MultiWii Configurator se todos os sensores respondem corretamente.

## 2. Configuração do Controle
# 2.1. Alimentação

- Insira a bateria apropriada no controle.
- Verifique se os joysticks retornam ao centro corretamente.

## 2.2. Verificação do Rádio

O controle utiliza um módulo NRF24L01 (long antenna).

Verifique se:
- o módulo está bem encaixado,
- a antena está posicionada corretamente,
- o LED de status indica transmissão.

Para testar:
- Ligue o controle.
- Ligue o drone.

Observe se o LED do receptor no drone acende indicando pareamento.

## 3. Utilização do Aplicativo Alternativo (App Inventor)

O aplicativo pode ser utilizado como método secundário de controle.

# 3.1. Pareamento Bluetooth

- Ative o Bluetooth no celular.
- Procure pelo dispositivo bluetooth do controle e pareie.
- Abra o app e conecte ao módulo.

# 3.2. Controle Básico

O aplicativo funciona como uma alternativa simplificada ao controle físico. Ele foi desenvolvido com dois conjuntos de botões direcionais, cada conjunto simulando um joystick do controle:

- Conjunto esquerdo → Throttle (aceleração) e Yaw (giro).
- Conjunto direito → Pitch (frente/trás) e Roll (direita/esquerda).

Dessa forma, o app mantém a lógica de dois joysticks, porém com botões que executam comandos discretos ao invés de movimentos analógicos.

## 4. Preparação para Voo
# 4.1. Checklist Pré-Voo

Antes de levantar voo:
- Coloque o drone em uma superfície plana.
- Ligue o controle antes de ligar o drone.
- Aguarde o pareamento completo.
- Arme o drone (combinação específica no MultiWii, geralmente yaw para direita + throttle mínimo).
- Verifique se as hélices giram ao dar throttle baixo.

# 4.2. Ambiente Recomendado

- Local amplo e sem obstáculos.
- Sem vento ou fluxo de ar forte.
- Chão plano e estável.

## 5. Execução do Voo

- Aumente o throttle lentamente.
- Faça pequenos ajustes de pitch, roll e yaw.
- Mantenha distância de pessoas, animais e objetos.
- Evite movimentos bruscos ao usar o app (pois ele é menos preciso que o controle com joysticks).

## 6. Finalização e Desligamento

- Aterre suavemente.
- Desarme o sistema via combinação do MultiWii.
- Desligue primeiro o drone e depois o controle.
- Desconecte a bateria.
- Armazene o drone em local seco e protegido.
