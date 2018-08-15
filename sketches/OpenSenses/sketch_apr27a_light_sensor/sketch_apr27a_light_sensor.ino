int ldr_pin =0; //variavel que representa o pino de entrada do sensor LDR 
int ldr_val=0; //variavel que representa o valor de entrada do pino analogico  "0"

void setup()
{
  pinMode(13,OUTPUT); //Led ligado a porta digital 13
  pinMode(12,OUTPUT);//Led ligado a porta digital  12
  pinMode(11,OUTPUT);//Led ligado a porta digital  11
  pinMode(10,OUTPUT);//Led ligado a porta digital  10
  pinMode(9,OUTPUT); //Led ligado a porta digital  9
Serial.begin(9600); // Variavel para ativar a porta serial e a velocidade da porta
}
void loop()
{
ldr_val = analogRead(ldr_pin); //variavel que lê o pino da ldr e sua variação de luz
Serial.println(ldr_val);       // variavel que escreve o valor da LDR na porta serial
delay(15);                     // intervalo de 15 Miliegundos
if(ldr_val >250)               // variavel que representa se a LDR for maio que 250 
  {
  digitalWrite(9,LOW);        //Acender o led na porta 9 do arduino 
  }  else                      // variavel que indentifica se o valor acima e verdadeiro pois se for falso executa:
   {
  digitalWrite(9,HIGH);}       //Apaga o led na porta 9 do arduino

if(ldr_val >200)              // variavel que representa se a LDR for maio que 200
  {
  digitalWrite(10,LOW);      
  }  else                    
   {
  digitalWrite(10,HIGH);}
if(ldr_val >150) 
  {
  digitalWrite(11,LOW);
  }  else
   {
  digitalWrite(11,HIGH);}
if(ldr_val >100) 
  {
  digitalWrite(12,LOW);
  }  else
   {
  digitalWrite(12,HIGH);}
  if(ldr_val>50)
  { 
    digitalWrite(13,LOW); 
  } else {
    digitalWrite(13,HIGH);
    }
}

