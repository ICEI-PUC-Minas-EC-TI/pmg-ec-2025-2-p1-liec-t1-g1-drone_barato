
# Materiais

Os materiais utilizados no projeto foram:
- Arduino Pro mini 5v 16Mhz
- ⁠Arduino nano 5v ATMEGA328
- ⁠5 x Reguladores de Tensao AMS1117
- ⁠Bateria Lipo 3.7v
- ⁠4 Motores sem Nucleo 716mm com 55.000RPM
- ⁠1x nrf24l01
- ⁠1 x nrf24l01 Com Antena
- ⁠Circuito Integrado PS2
- ⁠4x Diodo SS14
- ⁠4x Transistores AO3400
- ⁠4x Resistores 10k 1/4w
- ⁠MPU 6050 - Acelerometro
- ⁠Modulo HC-06 Bluetooth Slave
- ⁠Bateria 9V

# Desenvolvimento

## Desenvolvimento do Aplicativo

### Interface

A interface do aplicativo foi desenvolvida buscando simplicidade e fácil interação. A construção visual priorizou:
- listagem das informações que poderíamos conseguir com o drone em funcionamento;

### Código

A implementação do código do aplicativo foi realizada utilizando o ambiente de desenvolvimento do MIT APP Inventor. O código foi estruturado para:

- receber informações vindas do controle;
- exibir elas de forma organizada na tela;

## Desenvolvimento do Hardware

### Montagem

A montagem física do projeto envolveu:
- fixação da placa Arduino/ESP na estrutura;
- soldagem dos módulos e fios na placa perfurada;
- posicionamento dos sensores e atuadores conforme o funcionamento desejado;
- testes de segurança para ver se não havia possíveis curtos na soldagem dos fios e componentes;

O integrante responsável pela montagem principal organizou as etapas e garantiu que todos os componentes fossem instalados corretamente. Os demais integrantes auxiliaram em tarefas de preparação, suporte e aquisição dos materiais.

### Desenvolvimento do Código

O drone utiliza um código Arduino complexo e altamente versátil, baseado no firmware de multicópteros MultiWii, responsável por gerenciar praticamente todas as funções essenciais de voo. O MultiWii é organizado em diversas abas no código, permitindo controlar de forma separada funções como:
- leitura de sensores (acelerômetro e giroscópio);
- estabilização via controladores PID;
- gerenciamento individual dos motores;
- comunicação com o controle remoto;
- modos de voo e parâmetros avançados.
  
Apesar de ser um firmware robusto e amplo, muitas das funcionalidades presentes nas abas do MultiWii não foram utilizadas no projeto, já que o drone construído é uma versão simplificada, voltada apenas para o básico necessário para voo.

O código de voo utilizado pelo drone não foi desenvolvido por nosso grupo. Ele foi uma adaptação disponibilizada pelo criador original do tutorial, com créditos ao canal Electronoobs, que forneceu uma versão ajustada do MultiWii para drones pequenos. Essa base foi escolhida por já estar otimizada para o tipo de hardware utilizado, além de proporcionar estabilidade e confiabilidade durante o voo.

Para trabalhar com o firmware, foi necessário:
- conectar o drone ao computador por meio de um conversor FTDI;
- abrir o código completo, contendo todas as abas do MultiWii;
- carregar o firmware na placa controladora;
- ajustar parâmetros específicos do hardware utilizado;
- calibrar sensores e verificar a resposta dos motores.

Ou seja, mesmo não tendo programado o controle de voo do zero, o grupo realizou um trabalho essencial de compreensão, configuração, calibração e adaptação do firmware para o drone desenvolvido.

Diferentemente do firmware do drone, todo o sistema de controle foi desenvolvido integralmente por nós, tanto na versão física (com joysticks) quanto na versão digital (aplicativo Android).

O aplicativo foi criado para operar como um controle alternativo, utilizando dois conjuntos de setas para simular os dois joysticks tradicionais (esquerdo e direito). Essa abordagem simplificada permitiu:
- maior acessibilidade;
- controle via celular;
- redução de custos;
- facilidade de uso por iniciantes.

O controle físico, por sua vez, também foi programado totalmente pelo grupo, utilizando leitura analógica dos joysticks, envio de comandos por rádio e comunicação direta com o receptor do drone.

## Comunicação entre App e Hardware

A comunicação entre o aplicativo desenvolvido no MIT App Inventor e o drone foi projetada exclusivamente para receber dados de telemetria. Ou seja, o aplicativo não envia comandos de controle de voo — sua função é apenas exibir informações transmitidas pelo drone durante o funcionamento.

Como o módulo Bluetooth está conectado ao controle físico, e não diretamente ao drone, o controle atua como um intermediário na transmissão das informações.

A arquitetura final de comunicação ocorre em duas etapas:

### 1. Comunicação entre o Drone e o Controle (Rádio NRF24L01)

O drone envia constantemente seus dados de telemetria utilizando um módulo de rádio NRF24L01 instalado na placa controladora do drone. Os dados transmitidos podem incluir:
- valores lidos do acelerômetro/giroscópio (MPU6050);
- informações de estabilização e PID;
- status dos motores;
- tensões medidas;
- dados de orientação (pitch, roll, yaw);
- qualquer outro dado que o MultiWii esteja configurado para enviar.

O fluxo funciona assim:
- O drone coleta dados dos sensores e do firmware MultiWii.
- O Arduino do drone empacota essas informações.
- O NRF24L01 receptor (no drone) envia as informações ao
NRF24L01 transmissor presente no controle.
- O controle recebe os dados e prepara para enviá-los ao Bluetooth.

Assim, o controle funciona como um hub de retransmissão.

### 2. Comunicação entre o Controle e o Aplicativo (Bluetooth HC-06)

Após receber as informações enviadas via rádio pelo drone, o controle repassa esses dados para o aplicativo por meio do módulo Bluetooth HC-06.

O funcionamento ocorre da seguinte forma:
- o controle recebe os pacotes vindos do drone via NRF24L01;
- o microcontrolador interpreta os dados recebidos;
- esses dados são convertidos para um formato legível pelo aplicativo;
- o módulo HC-06 transmite via Bluetooth para o smartphone;
- o aplicativo exibe as informações em campos de texto específicos.

Nenhum comando de voo é enviado pelo aplicativo — sua função é apenas exibir telemetria em tempo real.
