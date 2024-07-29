#define TRIGGER_BACK_RIGHT 2
#define ECHO_BACK_RIGHT 3
#define TRIGGER_BACK_LEFT 4
#define ECHO_BACK_LEFT 5
#define TRIGGER_FRONT_RIGHT 6
#define ECHO_FRONT_RIGHT 7
#define TRIGGER_FRONT_LEFT 8
#define ECHO_FRONT_LEFT 9

void setup() {
  Serial.begin(9600);

  // Pin modlarını ayarla
  pinMode(TRIGGER_BACK_RIGHT, OUTPUT);
  pinMode(ECHO_BACK_RIGHT, INPUT);
  pinMode(TRIGGER_BACK_LEFT, OUTPUT);
  pinMode(ECHO_BACK_LEFT, INPUT);
  pinMode(TRIGGER_FRONT_RIGHT, OUTPUT);
  pinMode(ECHO_FRONT_RIGHT, INPUT);
  pinMode(TRIGGER_FRONT_LEFT, OUTPUT);
  pinMode(ECHO_FRONT_LEFT, INPUT);
}

void loop() {
  long duration;
  int distanceBackRight, distanceBackLeft, distanceFrontRight, distanceFrontLeft;

  // Sensörlerden mesafeyi al
  distanceBackRight = getDistance(TRIGGER_BACK_RIGHT, ECHO_BACK_RIGHT);
  distanceBackLeft = getDistance(TRIGGER_BACK_LEFT, ECHO_BACK_LEFT);
  distanceFrontRight = getDistance(TRIGGER_FRONT_RIGHT, ECHO_FRONT_RIGHT);
  distanceFrontLeft = getDistance(TRIGGER_FRONT_LEFT, ECHO_FRONT_LEFT);

  // Sonuçları Serial monitöre yazdır
  Serial.print("Arka Sağ: ");
  Serial.print(distanceBackRight);
  Serial.println(" cm");

  Serial.print("Arka Sol: ");
  Serial.print(distanceBackLeft);
  Serial.println(" cm");

  Serial.print("Ön Sağ: ");
  Serial.print(distanceFrontRight);
  Serial.println(" cm");

  Serial.print("Ön Sol: ");
  Serial.print(distanceFrontLeft);
  Serial.println(" cm");

  delay(500); // 0.5 saniye bekle
}

int getDistance(int triggerPin, int echoPin) {
  long duration;
  int distance;

  // Trigger pulse'u oluştur
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Echo pulse'ını ölç
  duration = pulseIn(echoPin, HIGH);

  // Mesafeyi hesapla (cm cinsinden)
  distance = duration * 0.0344 / 2;

  return distance;
}
