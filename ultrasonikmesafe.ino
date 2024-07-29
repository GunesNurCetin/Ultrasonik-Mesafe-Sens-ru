#define TRIGGER_PIN 9
#define ECHO_PIN 10

void setup() {
  Serial.begin(9600);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duration;
  int distance;

  // Trigger pulse'u oluştur
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Echo pulse'ını ölç
  duration = pulseIn(ECHO_PIN, HIGH);

  // Mesafeyi hesapla (cm cinsinden)
  distance = duration * 0.0344 / 2;

  // Sonuçları Serial monitöre yazdır
  Serial.print("Mesafe: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500); // 0.5 saniye bekle
}
