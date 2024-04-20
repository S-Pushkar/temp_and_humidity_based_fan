#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>

#define DHTPIN 7        
#define DHTTYPE DHT11  

#define MOTOR_PIN_ENA 9  
#define MOTOR_PIN_IN1 10 
#define MOTOR_PIN_IN2 11 

#define TEMPERATURE_THRESHOLD 28 
#define TEMPERATURE_THRESHOLD1 32

#define HUMIDITY_THRESHOLD 50.0

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(MOTOR_PIN_ENA, OUTPUT);
  pinMode(MOTOR_PIN_IN1, OUTPUT);
  pinMode(MOTOR_PIN_IN2, OUTPUT);
  Wire.begin();
}

void loop() {
  delay(2000); 
  float temperature = dht.readTemperature(); 
  float humidity = dht.readHumidity();
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    return;
  }
  if (isnan(humidity)) {
    Serial.println("Failed to read humidity from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  if (temperature >= TEMPERATURE_THRESHOLD1 && humidity >= HUMIDITY_THRESHOLD) {
    digitalWrite(MOTOR_PIN_IN1, HIGH);  
    digitalWrite(MOTOR_PIN_IN2, LOW);
    analogWrite(MOTOR_PIN_ENA, 255);   
    Serial.println("HIGH"); 
  }
  else if (temperature >= TEMPERATURE_THRESHOLD) {
    digitalWrite(MOTOR_PIN_IN1, HIGH); 
    digitalWrite(MOTOR_PIN_IN2, LOW);
    analogWrite(MOTOR_PIN_ENA, 100);    
    Serial.println("MEDIUM"); 
  }
  else {
    digitalWrite(MOTOR_PIN_IN1, HIGH);  
    digitalWrite(MOTOR_PIN_IN2, LOW);
    analogWrite(MOTOR_PIN_ENA, 0);   
    Serial.println("LOW"); 
  }

  Serial.println("-------------------------------------");
}