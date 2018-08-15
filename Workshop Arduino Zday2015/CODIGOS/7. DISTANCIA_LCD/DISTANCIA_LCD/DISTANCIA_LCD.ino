/*
  ZDAY 2014 - PORTO  
  Medidor de distâncias portátil
 */
// Inclusão da biblioteca com as funções para controlar o LCD 
#include <LiquidCrystal.h>

int pino_ativa_sensor = 13; // Porta digital associada ao pino de ativação do sensor
int pino_resultado_sensor = 12; // Porta digital associada ao pino do resultado do sensor
long tempo = 0; // Variável para guardar o tempo de voo
int distancia = 0; // Variável para guardar a conversão para centímetros

// Criação de uma variável do tipo LiquidCrystal e configuração dos pinos da 
// seguinte forma (rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  // Definir a porta digital associada à ativação do sensor como saída
  pinMode(pino_ativa_sensor, OUTPUT); 
  // Definir a porta digital associada ao resultado do sensor como entrada
  pinMode(pino_resultado_sensor, INPUT);
  // Configuração do número de colunas e linhas do display
  lcd.begin(16, 2); 
  // Coloca o cursor na posição inicial (coluna, linha) {começa 0}
  lcd.setCursor(0, 0); 
  // Escreve o texto apresentado no display
  lcd.print("   DISTANCIA:   "); 
}

// Parte do código que executa infinitamente
void loop() {
  digitalWrite(pino_ativa_sensor, LOW);  // Desativa saída digital
  delayMicroseconds(2);                  // Aguarda 2 microssegundos
  digitalWrite(pino_ativa_sensor, HIGH); // Ativa saída digital
  delayMicroseconds(5);                  // Aguarda 5 microssegundos
  digitalWrite(pino_ativa_sensor, LOW);  // Desativa saída digital
  tempo = pulseIn(pino_resultado_sensor, HIGH); // Leitura do tempo de voo
  distancia = tempo / 29 / 2; // Calculo da distancia em cm

  lcd.setCursor(0, 1);  // Coloca o cursor na coluna 0, linha 1
  lcd.print(distancia); // Envia a distancia lida para o display
  lcd.print(" cm  ");   // Escreve o simbolo de cm
  delay(200);           // Aguarda 200 ms
}



