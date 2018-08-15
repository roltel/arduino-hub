// Brilho 1 : vermelho
// Brilho 2 : verde
// Brilho 3 : azul

int brilho1 = 0, brilho2 = 0, brilho3 = 0;
float angulo = 0;
float pi = 3.14159265;
float minimo = 2.0 * pi / 180.0;
float intensidade = 0;
int r=10, g=11, b=12;

void setup()  { 
  // declare pin 9 to be an output:
  pinMode(r, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(b, OUTPUT);
  Serial.begin(9600);
} 
void loop()  { 
  intensidade = analogRead(5);
  intensidade = intensidade / 1023.0;
  brilho1 = ( sin(angulo + 2.0 * pi / 3.0 ) + 1 ) * 127.5 * intensidade;
  brilho2 = ( sin(angulo + 4.0 * pi / 3.0 ) + 1 ) * 127.5 * intensidade;
  brilho3 = ( sin(angulo) + 1 ) * 127.5 * intensidade;
  
  analogWrite(r, brilho1);    
  analogWrite(g, brilho2);
  analogWrite(b, brilho3);
  
  angulo = angulo + minimo;
  
  if (angulo >= 2.0 * pi) {
    angulo = 0;
  }
  delay(30);
  //Serial.println(intensidade * 1023);
  
}
