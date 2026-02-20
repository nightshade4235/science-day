// Pins for Ultrasonic Sensor
const int trigPin = 9;
const int echoPin = 10;

// Pin for Active Buzzer
const int buzzerPin = 11;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration;
  int distance;

  // Trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Logic: Active buzzers just need a HIGH signal to sound
  if (distance > 0 && distance <= 10) {
    digitalWrite(buzzerPin, HIGH); // Turn beep ON
  } else {
    digitalWrite(buzzerPin, LOW);  // Turn beep OFF
  }

  delay(100); 
}
