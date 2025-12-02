
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
- organização clara dos botões e comandos;

### Código

A implementação do código do aplicativo foi realizada utilizando o ambiente de desenvolvimento do MIT APP Inventor. O código foi estruturado para:

- capturar inputs do usuário através da interface;
- enviar comandos para o módulo bluetooth do controle;
- receber informações vindas do controle;

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

A comunicação entre o aplicativo desenvolvido no MIT App Inventor e o drone funciona como uma alternativa simples ao controle físico tradicional. Embora o drone possa ser pilotado diretamente pelo controle com joysticks, o app foi criado como um método secundário de operação, oferecendo comandos básicos via smartphone.

A arquitetura de comunicação ocorre em duas etapas principais:

1. Comunicação entre o Aplicativo e o Controle (Bluetooth)

O aplicativo envia sinais utilizando um módulo Bluetooth HC-05 conectado ao controle físico.
Diferente do controle com joysticks analógicos, o aplicativo foi projetado com setas direcionais simples, permitindo apenas comandos essenciais, como:
- subir / descer
- mover-se para frente / trás
- mover-se para esquerda / direita
- girar

Quando o usuário toca nas setas, o App Inventor envia esses comandos diretamente via Bluetooth para o controle.

2. Comunicação entre o Controle e o Drone (Rádio NRF24L01)

Após receber os comandos via Bluetooth, o controle interpreta as informações e envia os sinais para o drone utilizando um módulo de rádio NRF24L01 (long range antenna).
O processo funciona assim:
- O controle recebe os comandos via Bluetooth HC-06.
- O microcontrolador converte os comandos recebidos em pacotes adequados para o drone.
- O módulo NRF24L01 transmissor, instalado no controle, envia esses pacotes.
- O NRF24L01 receptor, presente no drone, recebe os dados e os entrega ao firmware MultiWii.
- O MultiWii interpreta os comandos e ajusta os motores para executar a ação desejada.

3. Integração entre os dois métodos de controle
   
- O controle físico utiliza joysticks reais e oferece controle mais preciso.
- O aplicativo foi criado como um controle alternativo e simplificado para testar o drone via smartphone.

Ambos enviam comandos a partir do controle, pois o smartphone nunca se comunica diretamente com o drone, apenas com o transmissor Bluetooth do controle.
