/*
  ZDAY 2014 - PORTO
  
  Controlo da lumiosidade de um LED
  
  O valor da lumiosidade é dado pela variação
  de um potenciómetro
 */

int potenciometro = 1; // Porta analógica associada ao potenciómetro
int led = 11;          // Porta digital associada ao LED
int valor = 0; // Variável para guardar o valor lido do potenciómetro

// Parte do código para configurações
void setup() {
  // Definir a porta digital associada ao LED como saída
  pinMode(led, OUTPUT); 
  // Configuração da velocidade comunicação da porta série
  Serial.begin(9600);
}

// Parte do código que executa infinitamente
void loop() {
  
  // Leitura do valor da porta analógica 1
  // isto é, o estado do potenciómetro
  valor = analogRead(potenciometro);
  // Envio o valor lido para o computador
  Serial.println(valor);
  // Alteração da luminosidade do LED
  // 0 valor devolvido pela leitura analógica é no máximo 1023
  // O valor máximo aceite pela seguite função é 255
  analogWrite(led, valor/4);
  delay(50); // Aguarda 50 ms)
}



