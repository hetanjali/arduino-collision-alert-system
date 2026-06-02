#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 8

void setup(){
  pinMode (TRIG_PIN , OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);

}

long getDistance(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

// Measure how long echo pin stays HIGH
long duration = pulseIn(ECHO_PIN , HIGH);

// Convert to cm: sound travels 343m/s = 0.0343 cm/µs
  // Divide by 2 because signal goes THERE and comes BACK

return duration * 0.0343/2;
}

void loop() {
  long distance = getDistance();
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
    // Beep faster as object gets closer
  if (distance < 10) {
    tone(BUZZER_PIN, 1000, 100);   // very fast beep
    delay(150);
  } else if (distance < 20) {
    tone(BUZZER_PIN, 1000, 100);
    delay(300);
  } else if (distance < 40) {
    tone(BUZZER_PIN, 1000, 100);
    delay(600);
  } else {
    noTone(BUZZER_PIN);            // silence beyond 40cm
  }
}