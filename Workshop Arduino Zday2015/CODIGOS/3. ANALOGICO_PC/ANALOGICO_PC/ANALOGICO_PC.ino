/*
  ZDAY 2014 - PORTO
  
  Leitura de um valor analógico
  e envio para o computador
  
  O valor analógico é dado pela variação
  de um potenciómetro
 */
 
int valor = 0; // Variável para guardar o valor lido
int potenciometro = 1; // Porta analógica associada ao potenciómetro

// Parte do código para configurações
void setup() {
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
  delay(500); // Aguarda meio segundo (500 ms)
}
