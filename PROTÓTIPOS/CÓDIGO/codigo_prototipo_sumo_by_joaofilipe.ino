void setup() {
  pinMode(2, OUTPUT);  // TRIG esquerda
  pinMode(3, INPUT);   // ECHO esquerda
  
  pinMode(4, OUTPUT);  // TRIG frente
  pinMode(5, INPUT);   // ECHO frente
  
  pinMode(6, OUTPUT);  // TRIG direita
  pinMode(7, INPUT);   // ECHO direita
  
  pinMode(8, OUTPUT);  // Motor esquerdo
  pinMode(9, OUTPUT);  // Motor direito
}

float medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duracao = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  if (duracao == 0) return -1; // sem leitura
  return duracao * 0.034 / 2;
}

void loop() {
  float distEsq = medirDistancia(2, 3);
  float distFrente = medirDistancia(4, 5);
  float distDir = medirDistancia(6, 7);

  const float limite = 100.0; // distância máxima para "ver" o oponente (em cm)

  // Estratégia de decisão
  if (distFrente > 0 && distFrente < limite) {
    // Inimigo à frente → avançar com tudo
    digitalWrite(8, HIGH); // motor esquerdo
    digitalWrite(9, HIGH); // motor direito
  }
  else if (distEsq > 0 && distEsq < limite) {
    // Inimigo à esquerda → gira para esquerda (liga motor direito)
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
  }
  else if (distDir > 0 && distDir < limite) {
    // Inimigo à direita → gira para direita (liga motor esquerdo)
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  }
  else {
    // Sem inimigo → para
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
  }