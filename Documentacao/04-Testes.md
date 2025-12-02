### Testes do Projeto

## 1. Testes dos Motores

Inicialmente, foram realizados testes individuais em cada um dos quatro motores com o objetivo de:

- verificar o sentido de rotação;
- garantir que nenhum motor apresentava falhas mecânicas ou elétricas;
- confirmar que todos os ESCs estavam enviando o sinal corretamente.

Após validar o funcionamento individual, foi realizado um teste conjunto com os quatro motores ligados simultaneamente. Esse teste permitiu identificar:

- inconsistências na distribuição de potência;
- vibrações excessivas devido à estrutura impressa em 3D;
- necessidade de reforçar algumas partes do chassi (que, posteriormente, chegaram a quebrar durante o uso).

Os testes demonstraram que, apesar do funcionamento geral estar correto, pequenas falhas estruturais no corpo do drone — possivelmente relacionadas à qualidade do filamento utilizado — comprometeram a robustez da montagem.

## 2. Testes de Condutividade e Continuidade

Para garantir que todo o circuito estivesse funcionando corretamente, foram feitos diversos testes com multímetro tanto no drone quanto no controle remoto físico. Esses testes incluíram:

- verificação de continuidade nos fios ligados aos motores e ESCs;
- teste dos pontos de solda;
- conferência da alimentação elétrica (tensões corretas);
- detecção de possíveis curtos ou falhas de contato.

No caso do controle, os testes de condutividade foram fundamentais para identificar possíveis falhas nos módulos utilizados, especialmente nas conexões feitas com jumpers. Após alguns testes, foi observado que:

- certos módulos começaram a apresentar leituras irregulares;
- alguns sinais chegavam inconsistentes ao microcontrolador;
- a sensibilidade com fios jumper prejudicou a estabilidade geral do sistema.

Esses problemas foram atribuídos ao uso de conexões temporárias, que não são ideais para projetos que dependem de precisão e estabilidade.

## 3. Testes do Aplicativo (Controle Digital)

O aplicativo Android também passou por testes práticos para verificar o envio de comandos e o funcionamento das setas em substituição aos joysticks. Os testes mostraram:

- funcionamento estável;
- boa responsividade;
- comunicação consistente durante a operação.

O controle digital conseguiu comunicar e trocar informações com o controle. Infelizmente não conseguimos testar essa conexão com o drone, pois após a montagem do mesmo, os problemas de transferência de energia dos módulos do controle surgiram.

## Resultados e Limitações Identificadas

# Resultados positivos:

- Motores funcionaram corretamente após calibração;
- Firmware MultiWii respondeu bem aos comandos;
- Estrutura do drone suportou os testes iniciais;
- Controle digital operou de forma estável;

Limitações observadas:

- Uso de jumpers prejudicou a confiabilidade do controle físico;
- Alguns módulos do controle físico apresentaram falhas intermitentes;
- Estrutura impressa em 3D mostrou fragilidade em pontos específicos;
- Dependência de um firmware pré-existente limita personalização profunda;
- Ausência de sensores como acelerômetro e giroscópio no controle reduz precisão.
