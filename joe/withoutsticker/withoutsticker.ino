// Pins for Ultrasonic Sensor
const int trigPin = 9;
const int echoPin = 10;

// Pin for Passive Buzzer
const int buzzerPin = 11;

// Tone frequency (1000Hz is a standard beep)
const int toneFreq = 1000; 

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600); // For monitoring distance on your computer
}

void loop() {
  long duration;
  int distance;
  
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor by sending a 10 microsecond pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance (Speed of sound is ~0.034 cm/us)
  distance = duration * 0.034 / 2;

  // Print distance to Serial Monitor (Tools > Serial Monitor)
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Logic: If something is 10cm or closer
  if (distance > 0 && distance <= 10) {
    tone(buzzerPin, toneFreq); 
  } else {
    noTone(buzzerPin); // Silence when out of range
  }
  
  delay(100); // Wait 100ms before the next reading
}
