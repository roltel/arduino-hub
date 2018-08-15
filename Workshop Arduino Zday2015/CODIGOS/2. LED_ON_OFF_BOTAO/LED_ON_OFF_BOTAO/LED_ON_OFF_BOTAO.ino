/*
  ZDAY 2014 - PORTO
  
  LED controlado com botão
  
  Este código permite que quando um botão é
  pressionado, um LED fique aceso
 */

int led =  11; // Porta digital associada ao LED
int botao = 10; // Porta digital associada ao botão

int estado_botao = 0; // Variável que guardará o estado do botão

// Parte do código para configurações
void setup() {
    // Definir a porta digital associada ao LED como saída
  pinMode(led, OUTPUT);      
    // Definir a porta digital associada ao botão como entrada
  pinMode(botao, INPUT);     
}

// Parte do código que executa infinitamente
void loop(){
  // Guarda o estado do botão na variável estado_botao
  estado_botao = digitalRead(botao);

  // Se o botão estiver premido
  if (estado_botao == HIGH) {     
    // Liga o LED    
    digitalWrite(led, HIGH);  
  } 
  // Caso o botão não esteja premido
  else {
    // Desliga o LED 
    digitalWrite(led, LOW); 
  }
}
