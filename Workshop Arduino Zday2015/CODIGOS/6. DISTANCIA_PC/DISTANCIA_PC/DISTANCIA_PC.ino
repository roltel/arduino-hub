/*
  ZDAY 2014 - PORTO  
  Medidor de distâncias
 */

int pino_ativa_sensor = 13; // Porta digital associada ao pino de ativação do sensor
int pino_resultado_sensor = 12; // Porta digital associada ao pino do resultado do sensor
long tempo = 0; // Variável para guardar o tempo de voo
int distancia = 0; // Variável para guardar a conversão para centímetros

void setup() {
  // Definir a porta digital associada à ativação do sensor como saída
  pinMode(pino_ativa_sensor, OUTPUT); 
  // Definir a porta digital associada ao resultado do sensor como entrada
  pinMode(pino_resultado_sensor, INPUT);
  // Configuração da velocidade comunicação da porta série
  Serial.begin(9600);
}

// Parte do código que executa infinitamente
void loop() {
  // Para ativar o sensor, é necessário emitir um pulso, pelo que
  // colocamos a porta no estado LOW, colocamos depois como HIGH
  // e por fim novamente LOW
  digitalWrite(pino_ativa_sensor, LOW);  // Desativa saída digital
  delayMicroseconds(2);                  // Aguarda 2 microssegundos
  digitalWrite(pino_ativa_sensor, HIGH); // Ativa saída digital
  delayMicroseconds(5);                  // Aguarda 5 microssegundos
  digitalWrite(pino_ativa_sensor, LOW);  // Desativa saída digital

  // O sensor devolve um pulso proporcional ao tempo que passou entre
  // a emissão e a receção do sinal. A função seguinte conta quantos
  // microssegundos este pulso dura e guarda o valor na variável tempo
  tempo = pulseIn(pino_resultado_sensor, HIGH);
  // O som percorre 340 m/s a 15ºC, o que corresponde aproximadamente a
  // 29 microssegundos por centimetro. Como o tempo contado é o de ida e 
  // o de volta, tem de se dividir por dois
  distancia = tempo / 29 / 2;
  Serial.print(distancia); // Envia a distância obtida para o PC
  Serial.println(" cm");   // Envia o texto " cm" e nova linha  
  delay(200); // Aguarda 200 ms
}



