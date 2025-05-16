const int IN1 = 3;
const int IN2 = 4;
const int ENA = 2;

const int IN3 = 7;
const int IN4 = 6;
const int ENB = 5;

const int trigFrontal = 8;
const int echoFrontal = 9;

const int trigLateral = 12;
const int echoLateral = 11;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(trigFrontal, OUTPUT);
  pinMode(echoFrontal, INPUT);
  pinMode(trigLateral, OUTPUT);
  pinMode(echoLateral, INPUT);

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
  float distanciaLateral = medirDistancia(trigLateral, echoLateral);

  Serial.print("Frente: ");
  Serial.print(distanciaFrontal);
  Serial.print(" cm | Lado: ");
  Serial.print(distanciaLateral);
  Serial.println(" cm");

  if (distanciaLateral < 20 && distanciaLateral > 0) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
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
