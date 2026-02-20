// Ultrasonic Distance Buzzer for Blind Assistance
#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 3  // Must be PWM pin for volume control

const int MAX_DISTANCE_CM = 200;  // 2m - faint sound
const int MIN_DISTANCE_CM = 2;    // 2cm - max loud
const int MAX_VOLUME = 127;       // Max PWM for loudest (50% duty cycle)
const int MIN_VOLUME = 20;        // Min PWM for very faint (adjust if too quiet)
const int MID_DISTANCE_CM = 100;  // 1m - for reference, but mapping is linear

void setup() {
  Serial.begin(9600);  // Debugging
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  analogWrite(BUZZER_PIN, 0);  // Start silent
}

void loop() {
  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance (cm)
  int distance = duration * 0.034 / 2;

  // Debug print
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Volume logic
  if (distance >= MIN_DISTANCE_CM && distance <= MAX_DISTANCE_CM) {
    // Map distance to volume: closer = louder (higher PWM value up to 127)
    int volume = map(distance, MIN_DISTANCE_CM, MAX_DISTANCE_CM, MAX_VOLUME, MIN_VOLUME);
    analogWrite(BUZZER_PIN, volume);
  } else {
    analogWrite(BUZZER_PIN, 0);  // Silent if out of range
  }

  delay(100);  // Refresh rate - lower for faster response, but avoid overwhelming
}
