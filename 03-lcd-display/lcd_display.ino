#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 8

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.0343 / 2;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.print("Collision Alert");
  lcd.setCursor(0, 1);
  lcd.print("System Ready!");
  delay(2000);
  lcd.clear();
  
  Serial.begin(9600);
}

void loop() {
  long distance = getDistance();
  
  // Update LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm  ");
  
  // Show status on LCD row 2
  lcd.setCursor(8, 1);
  if (distance < 10) {
    lcd.print("CRITICAL");
  } else if (distance < 20) {
    lcd.print("DANGER  ");
  } else if (distance < 40) {
    lcd.print("WARNING ");
  } else {
    lcd.print("SAFE    ");
  }
  
  // Buzzer alerts
  if (distance < 10) {
    tone(BUZZER_PIN, 1000, 100);
    delay(150);
  } else if (distance < 20) {
    tone(BUZZER_PIN, 1000, 100);
    delay(300);
  } else if (distance < 40) {
    tone(BUZZER_PIN, 1000, 100);
    delay(600);
  } else {
    noTone(BUZZER_PIN);
    delay(200);
  }
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}