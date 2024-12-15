#include <DHT.h>
// Set your respective pins here
const int dhtPin = 3;        // Pin connected to the DHT11 data pin
const int trigPin1 = 11;      // Pin connected to ultrasonic sensor 1 TRIG
const int echoPin1 = 10;     // Pin connected to ultrasonic sensor 1 ECHO
const int trigPin2 = 8;      // Pin connected to ultrasonic sensor 2 TRIG
const int echoPin2 = 9;      // Pin connected to ultrasonic sensor 2 ECHO
const int doorSensorPin = 7; // Pin connected to the reed switch (door sensor)

DHT dht(dhtPin, DHT11);      // Initialize DHT11 sensor

long duration1, duration2;
int distance1, distance2;
int doorState = 0;   // Variable to store door state (0 = open, 1 = closed)

void setup() {
  Serial.begin(9600);         // Start serial communication
  dht.begin();                // Initialize the DHT sensor
  pinMode(trigPin1, OUTPUT);  // Set TRIG pins as OUTPUT
  pinMode(echoPin1, INPUT);   // Set ECHO pins as INPUT
  pinMode(trigPin2, OUTPUT);  
  pinMode(echoPin2, INPUT);
  pinMode(doorSensorPin, INPUT_PULLUP); // Enable internal pull-up resistor for reed switch
}

void loop() {
  // --- Read Temperature and Humidity from DHT11 ---
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Temperature in Celsius

  // Check if reading failed and try again
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // --- Read Distance from Ultrasonic Sensor 1 ---
  digitalWrite(trigPin1, LOW); 
  delayMicroseconds(2);  // Wait for 2 microseconds
  digitalWrite(trigPin1, HIGH); 
  delayMicroseconds(10); // Send 10 microseconds pulse
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);  // Read the pulse duration from ECHO pin
  distance1 = duration1 * 0.0344 / 2;   // Calculate the distance (in cm)

  // --- Read Distance from Ultrasonic Sensor 2 ---
  digitalWrite(trigPin2, LOW); 
  delayMicroseconds(2);  // Wait for 2 microseconds
  digitalWrite(trigPin2, HIGH); 
  delayMicroseconds(10); // Send 10 microseconds pulse
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);  // Read the pulse duration from ECHO pin
  distance2 = duration2 * 0.0344 / 2;   // Calculate the distance (in cm)

  // --- Read Door Sensor (Reed Switch) ---
  doorState = digitalRead(doorSensorPin);  // Read the state of the door sensor
  
  // Print results to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C  | Humidity: ");
  Serial.print(humidity);
  Serial.print(" %  | ");
  
  if (doorState == LOW) {
    Serial.print("Door Closed  | ");
  } else {
    Serial.print("Door Open  | ");
  }

  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.print(" cm  | Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  delay(1000);  // Delay before the next reading
}
