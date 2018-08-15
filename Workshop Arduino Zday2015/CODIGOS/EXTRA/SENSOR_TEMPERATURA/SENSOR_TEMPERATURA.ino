
int temperatura=2;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  analogReference(DEFAULT); // Tensão de referência
}

void loop() {
  sensorValue = 0;
  while(1){
  sensorValue = (float)analogRead(A3) * 5000 / 1023 / 10 - 50;
  Serial.println("Sensor1: ");
  Serial.println(sensorValue);
  delay(500);
  //digitalWrite(13, LOW);
  delay(500);
  //digitalWrite(13, HIGH);
  }
}
