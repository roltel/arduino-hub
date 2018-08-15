/*
  ZDAY 2014 - PORTO
  
  Piscar um LED
  
  Este código liga e desliga um LED
  associado à saída digital 11 a cada segundo
 */

// Variável que guarda a porta digital a utilizar 
int led = 11;

// Parte do código para configurações
void setup() {                
  // Definir a porta digital associada ao LED como saída
  pinMode(led, OUTPUT);     
}

// Parte do código que executa infinitamente
void loop() {
  digitalWrite(led, HIGH);   // Liga o LED (ativa a porta digital)
  delay(1000);               // Aguarda 1 segundo (1000 ms)
  digitalWrite(led, LOW);    // Desliga o LED (desativa a porta digital)
  delay(1000);               // Aguarda 1 segundo (1000 ms)
}



