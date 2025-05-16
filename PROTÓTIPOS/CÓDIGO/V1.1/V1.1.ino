const int IN1 = 3;
const int IN2 = 4;
const int ENA = 2;

const int IN3 = 7;
const int IN4 = 6;
const int ENB = 5;

const int trigFrontal = 8;
const int echoFrontal = 9;

const int trigDireito = 11;
const int echoDireito = 10;

const int trigEsquerdo = 12;
const int echoEsquerdo = 13;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(trigFrontal, OUTPUT);
  pinMode(echoFrontal, INPUT);
  pinMode(trigDireito, OUTPUT);
  pinMode(echoDireito, INPUT);
  pinMode(trigEsquerdo, OUTPUT);
  pinMode(echoEsquerdo, INPUT);

  Serial.begin(9600);
}

float medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  long duracao = pulseIn(echoPin, HIGH, 30000);
  return duracao * 0.034 / 2;
}

void loop() {
  float distanciaFrontal = medirDistancia(trigFrontal, echoFrontal);
  float distanciaDireita = medirDistancia(trigDireito, echoDireito);
  float distanciaEsquerda = medirDistancia(trigEsquerdo, echoEsquerdo);

  Serial.print("Frente: ");
  Serial.print(distanciaFrontal);
  Serial.print(" cm Direita: ");
  Serial.print(distanciaDireita);
  Serial.print(" cm Esquerda: ");
  Serial.print(distanciaEsquerda);
  Serial.println(" cm");

  if (distanciaDireita < 30 && distanciaDireita > 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 200);
    analogWrite(ENB, 200);
  }
  else if (distanciaEsquerda < 30 && distanciaEsquerda > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 200);
    analogWrite(ENB, 200);
  }
  else if (distanciaFrontal < 30 && distanciaFrontal > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 200);
    analogWrite(ENB, 200);
  }
  else {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
  }
}
