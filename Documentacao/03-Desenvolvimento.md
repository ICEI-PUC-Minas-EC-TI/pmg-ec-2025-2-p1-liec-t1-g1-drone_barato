
# Materiais

Os materiais utilizados no projeto foram:
- Liste os materiais usados no projeto, como Arduino/ESP, sensores, atuadores e outros.

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

O drone utiliza um código Arduino complexo e altamente versátil, baseado no software de multicópteros MultiWii, que é responsável por gerenciar praticamente todas as funções de voo. O MultiWii é estruturado em múltiplas abas dentro do código, permitindo controlar separadamente funções como:
- leitura dos sensores (acelerômetro/giroscópio),
- estabilização por PID,
- gerenciamento dos motores,
- comunicação com o controle remoto,
- modos de voo e parâmetros avançados.

Embora seja um firmware robusto e abrangente, muitas das funcionalidades presentes nas abas do MultiWii não foram utilizadas neste projeto, já que o drone construído é uma versão simplificada e focada apenas no essencial para voo.

O código utilizado no projeto não foi desenvolvido do zero por nós. Ele foi uma adaptação disponibilizada pelo criador original do tutorial, com créditos ao canal Electronoobs, que disponibilizou uma versão ajustada do MultiWii para drones pequenos. Essa base foi escolhida porque já estava otimizada para o tipo de hardware utilizado e oferecia estabilidade e confiabilidade durante o voo.

Para trabalhar com o firmware, foi necessário:
- conectar o drone ao computador por meio de um conversor FTDI,
- abrir o código completo, contendo todas as abas do MultiWii,
- carregar esse firmware na placa controladora (Arduino),
- ajustar parâmetros específicos do hardware utilizado,
- calibrar sensores e verificar a resposta dos motores.

Ou seja, embora nosso grupo não tenha programado o controle de voo do zero, houve um trabalho importante de compreensão, configuração, calibração e adaptação do firmware ao projeto construído. O MultiWii executa a maior parte das funções críticas do drone, e o papel do grupo foi garantir que tudo estivesse alinhado ao hardware desenvolvido.

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
