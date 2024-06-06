#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 16);

int turbidityPin = A0; // A0 for Arduino/36 for ESP
int cloudyMotorPin = 7; // Digital pin for cloudy water motor
int clearMotorPin = 8;  // Digital pin for clear water motor

void setup() {
  Serial.begin(9600);
  // Initialize LCD
  lcd.init();
  // Turn on LCD backlight
  lcd.backlight();
  
  // Set motor pins as output
  pinMode(cloudyMotorPin, OUTPUT);
  pinMode(clearMotorPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(turbidityPin);
  int turbidity = map(sensorValue, 0, 750, 100, 0);
  
  Serial.print("Turbidity: ");
  Serial.println(turbidity);

  lcd.setCursor(0, 0);
  
  if (turbidity < 20) {
    Serial.println("CLEAR");
    lcd.print("                "); // Clear the line
    lcd.setCursor(0, 0);
    lcd.print("CLEAR");
    // Turn on clear water motor
    digitalWrite(clearMotorPin, HIGH);
    delay(5000); // Keep motor on for 5 seconds
    // Turn off clear water motor
    digitalWrite(clearMotorPin, LOW);
  } 
  else if (turbidity <= 50) {
    Serial.println("CLOUDY");
    lcd.print("                "); // Clear the line
    lcd.setCursor(0, 0);
    lcd.print("CLOUDY");
    // Turn on cloudy water motor
    digitalWrite(cloudyMotorPin, HIGH);
    delay(5000); // Keep motor on for 5 seconds
    // Turn off cloudy water motor
    digitalWrite(cloudyMotorPin, LOW);
  } 
  else {
    Serial.println("DIRTY");
    lcd.print("                "); // Clear the line
    lcd.setCursor(0, 0);
    lcd.print("DIRTY");
    // Turn off both motors
    digitalWrite(cloudyMotorPin, LOW);
    digitalWrite(clearMotorPin, LOW);
  }

  delay(50); // Adjust delay as needed for stability
}


