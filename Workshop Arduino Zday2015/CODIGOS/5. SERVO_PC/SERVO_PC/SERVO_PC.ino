/*
  ZDAY 2014 - PORTO
  
  Controlo de um servomotor
  
  O ângulo do servomotor será dado pelo potenciómetro
 */
 
// Bilioteca que contém todas as funções a utilizar
#include <Servo.h> 

// Variável do tipo Servo que está
// associada ao controlo do servomotor  
Servo servomotor;  

int pin_servomotor = 9; // Porta digital associada ao servomotor
int potenciometro = 1; // Porta analógica associada ao potenciómetro
int valor = 0; // Variável para guardar o valor lido do potenciómetro
 
// Parte do código para configurações
void setup() {
  // Associa a porta digital 9 ao servomotor
  servomotor.attach(pin_servomotor); 
  // Configuração da velocidade comunicação da porta série
  Serial.begin(9600); 
} 
 
// Parte do código que executa infinitamente
void loop() {
  // Leitura do valor da porta analógica 1
  // isto é, o estado do potenciómetro
  valor = analogRead(potenciometro);
  // 0 valor devolvido pela leitura analógica é no máximo 1023
  // A seguinte função 'dimensiona' o valor para o intervalo pretendido
  valor = map(valor, 0, 1023, 0, 180);    
  // Alteração da posição do servomotor
  servomotor.write(valor); 
  Serial.println(valor);  // Envia o ângulo para o computador
  delay(20); // Dá tempo para o servomotor chegar ao ângulo                         
}




