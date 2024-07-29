#define TRIGGER_BACK_RIGHT 2
#define ECHO_BACK_RIGHT 3
#define TRIGGER_BACK_LEFT 4
#define ECHO_BACK_LEFT 5
#define TRIGGER_FRONT_RIGHT 6
#define ECHO_FRONT_RIGHT 7
#define TRIGGER_FRONT_LEFT 8
#define ECHO_FRONT_LEFT 9

// Mesafe eşik değerleri (cm cinsinden)
#define DISTANCE_THRESHOLD 10

void setup() {
  Serial.begin(9600);

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
  int distanceBackRight = getDistance(TRIGGER_BACK_RIGHT, ECHO_BACK_RIGHT);
  int distanceBackLeft = getDistance(TRIGGER_BACK_LEFT, ECHO_BACK_LEFT);
  int distanceFrontRight = getDistance(TRIGGER_FRONT_RIGHT, ECHO_FRONT_RIGHT);
  int distanceFrontLeft = getDistance(TRIGGER_FRONT_LEFT, ECHO_FRONT_LEFT);

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

  // Ortalamayı kontrol et
  centerVehicle(distanceFrontRight, distanceFrontLeft, distanceBackRight, distanceBackLeft);

  delay(500); // 0.5 saniye bekle
}

int getDistance(int triggerPin, int echoPin) {
  long duration;
  int distance;

  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0344 / 2;

  return distance;
}

void centerVehicle(int frontRight, int frontLeft, int backRight, int backLeft) {
  // Hesaplamaları yaparak aracın ortalanıp ortalanmadığını kontrol et
  int frontAverage = (frontRight + frontLeft) / 2;
  int backAverage = (backRight + backLeft) / 2;
  int leftRightDifference = abs(frontLeft - frontRight);
  int backDifference = abs(backRight - backLeft);

  // Ortalamayı yapma işlemleri
  if (leftRightDifference > DISTANCE_THRESHOLD) {
    if (frontLeft > frontRight) {
      Serial.println("Aracı sağa hareket ettirin.");
      // Sağ motoru çalıştırın veya sağa dönme komutu verin
    } else {
      Serial.println("Aracı sola hareket ettirin.");
      // Sol motoru çalıştırın veya sola dönme komutu verin
    }
  } else if (backDifference > DISTANCE_THRESHOLD) {
    if (backLeft > backRight) {
      Serial.println("Aracı geri hareket ettirin.");
      // Arka motorları çalıştırın veya geri gitme komutu verin
    } else {
      Serial.println("Aracı ileri hareket ettirin.");
      // Ön motorları çalıştırın veya ileri gitme komutu verin
    }
  } else {
    Serial.println("Araç ortalanmış durumda.");
    // Araç doğru şekilde ortalanmış
  }
}
