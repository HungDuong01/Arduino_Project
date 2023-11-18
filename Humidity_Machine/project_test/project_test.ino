#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN 2
#define RELAY_PIN 3

// Type of DHT sensor
#define DHTTYPE DHT11
// PIN set up to the LCD
int rs = 7; // data/instruction select bit
int e = 8; // enable bit 
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;
LiquidCrystal lcd(7,8,9,10,11,12);
//Initialize DHT sensor
DHT dht(DHTPIN,DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // Turn the relay off initially
  pinMode(RELAY_PIN, OUTPUT);
  
  digitalWrite(RELAY_PIN, HIGH);
  
  // Start the sensor and LCD
  dht.begin();
  lcd.begin(16,2);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 float humid = dht.readHumidity();

  // Read temperature
  float temp = dht.readTemperature();
  lcd.setCursor(0,0); // Display the temperature on LCD
  lcd.print("Temp (C) = ");
  lcd.print(temp);
  lcd.setCursor(0,1); // Display the humidity on LCD
  lcd.print("Humidity = ");
  lcd.print(humid);
  delay(1000); // delay 1s
  lcd.clear(); // Clear the previous capture every 1s 
  // If humidity level stays below 20, keep humidifier ON
  if (humid < 20) {   // if humidity is below 10%
    digitalWrite(RELAY_PIN, LOW);  // Writes a LOW signal to relay
  // If it over or equal to 20, turn the humidifier OFF
  } else {
    digitalWrite(RELAY_PIN, HIGH);  // Writes a HIGH signal to relay
   
  }
   
}
 