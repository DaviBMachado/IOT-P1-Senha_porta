# Artigo: Smart Lock - Fechadura de Acesso Inteligente (IoT)

## Nome do Projeto: Smart Lock - Fechadura de Acesso Inteligente com Gestão de Energia.

### Descrição do Funcionamento:
O projeto consiste em um sistema de segurança IoT para controle de acesso físico. O sistema opera majoritariamente em um estado de "standby" (espera) para otimização de energia, mantendo a porta trancada e o display desligado. Quando uma pessoa se aproxima, o sistema é "acordado" e o display solicita a digitação de uma senha de 4 dígitos.

Se a senha estiver correta, a trava é liberada e a porta é aberta. Caso a senha esteja incorreta, uma mensagem de erro é exibida e o sistema solicita uma nova tentativa. Há também um sistema de timeout: se o sistema não detectar movimento ou interação por 5 segundos contínuos, a operação é cancelada e o dispositivo retorna automaticamente ao modo de economia de energia. O trancamento da porta pode ser feito manualmente a qualquer momento pressionando a tecla "C".

### Recursos Utilizados:
Para a construção do protótipo na plataforma Tinkercad, foram empregados os seguintes recursos de hardware (simulados):

- placa Controladora: 1x Arduino Uno R3.
- Sensor 1 (Detecção): 1x Sensor de Movimento/Presença (PIR).
- Sensor 2 (Entrada de Dados): 1x Teclado Matricial 4x4 (Keypad).
- Atuador: 1x Micro Servo Motor.
- Dispositivo de Saída Visual: 1x Display LCD 16x2 com módulo I2C (PCF8574).

### Conceitos dos Sensores e Atuadores Utilizados
Para compreender a arquitetura do projeto, é fundamental entender os princípios físicos e lógicos de cada componente:

- Sensor PIR (Passive Infrared):  Este é um sensor eletrônico que mede a luz infravermelha irradiada por objetos em seu campo de visão. Ele não emite energia, apenas detecta passivamente a variação de calor (como o calor do corpo humano) em movimento no ambiente. Quando há variação brusca, ele envia um sinal de nível lógico ALTO (HIGH) para o Arduino.

- Teclado Matricial 4x4: Funciona com base em uma matriz de linhas e colunas interligadas. Em vez de usar 16 pinos do Arduino para 16 botões, ele usa apenas 8 pinos (4 linhas e 4 colunas). O controlador faz uma varredura (multiplexação) enviando sinais pelas linhas e lendo as colunas para identificar a coordenada exata da tecla pressionada.

- Micro Servo Motor:  Um atuador rotativo que permite controle preciso da posição angular. Ele é composto por um motor DC, um conjunto de engrenagens e um circuito de controle com um potenciômetro interno. O Arduino envia pulsos elétricos (PWM - Pulse Width Modulation) que indicam ao motor para qual ângulo (de 0º a 180º) o eixo deve girar.

- Display LCD 16x2 com I2C: Uma tela de cristal líquido capaz de exibir 16 caracteres em 2 linhas. A adição do módulo I2C é essencial na Internet das Coisas e sistemas embarcados, pois reduz drasticamente a quantidade de fios necessários de cerca de 6 para apenas 2 (SDA para dados e SCL para o relógio da comunicação).

### Circuito e Programação
![alt text](image.png)

### Sobre a Programação:
Para atender à complexidade da regra de negócios do projeto — especificamente o uso de temporizadores não-bloqueantes (millis()) para o modo standby e a integração de bibliotecas externas para a comunicação I2C e o mapeamento da matriz do teclado — a programação foi integralmente desenvolvida em linguagem C++ (Texto). Essa abordagem proporciona maior controle sobre o hardware e a gestão de memória do microcontrolador em comparação à programação em blocos.

### Resumo e Considerações Finais
O projeto "Smart Lock" atinge seu objetivo de simular um sistema de acesso seguro e inteligente. A implementação da lógica de inatividade (timeout) através de funções não-bloqueantes resolve um problema comum em sistemas embarcados: o desperdício de energia.

Para a sua trajetória no curso de Desenvolvimento de Software na Fatec Prefeito Hirant Sanazar, projetos como este são excelentes laboratórios. Eles demonstram não apenas a montagem de circuitos básicos, mas principalmente a aplicação de conceitos sólidos de engenharia de software — como controle de estados, modularização e economia de processamento — interagindo diretamente com o mundo físico através da Internet das Coisas.