#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// I2C address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  
  // Welcome message
  lcd.setCursor(0, 0);
  lcd.print("I2C LCD Ready!");
  lcd.setCursor(0, 1);
  lcd.print("Hetanjali :)");
  delay(2000);
  lcd.clear();
}

int counter = 0;

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Counter:");
  lcd.setCursor(0, 1);
  lcd.print(counter);
  lcd.print("  ");
  
  counter++;
  delay(1000);
  
  // Reset after 100
  if (counter > 100) {
    counter = 0;
    lcd.clear();
  }
}
