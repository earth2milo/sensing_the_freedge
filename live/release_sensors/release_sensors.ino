#include <DHT.h>

const int dhtPin = 3;        // Pin connected to the DHT11 data pin
const int trigPin1 = 11;     // Pin connected to ultrasonic sensor 1 TRIG
const int echoPin1 = 10;     // Pin connected to ultrasonic sensor 1 ECHO
const int trigPin2 = 8;      // Pin connected to ultrasonic sensor 2 TRIG
const int echoPin2 = 9;      // Pin connected to ultrasonic sensor 2 ECHO
const int doorSensorPin = 7; // Pin connected to the reed switch (door sensor)

DHT dht(dhtPin, DHT11);      // Initialize DHT11 sensor

long duration1, duration2;
int distance1, distance2;
int prevDistance1, prevDistance2; // Baseline readings for comparison
bool doorOpen = false;  // Door open state
bool initialized = false; // Flag for first baseline reading

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
  // --- Read Door Sensor ---
  doorOpen = (digitalRead(doorSensorPin) == HIGH); // HIGH = Door Open, LOW = Door Closed

  // --- Handle Door Logic ---
  if (doorOpen) {
    Serial.println("Door is Open!");
    readUltrasonicSensors(); // Read sensors actively when door is open
  } else {
    Serial.println("Door is Closed!");
    
    if (!initialized) {
      // Set initial baseline when the fridge is first closed
      prevDistance1 = readSingleUltrasonic(trigPin1, echoPin1);
      prevDistance2 = readSingleUltrasonic(trigPin2, echoPin2);
      initialized = true;
      Serial.println("Initialized baseline readings!");
    }

    // Check for changes after the door closes
    int newDistance1 = readSingleUltrasonic(trigPin1, echoPin1);
    int newDistance2 = readSingleUltrasonic(trigPin2, echoPin2);

    if (abs(newDistance1 - prevDistance1) > 5 || abs(newDistance2 - prevDistance2) > 5) {
      Serial.println("Change detected! Food has been added or removed.");
    } else {
      Serial.println("No significant change detected.");
    }

    // Update baseline
    prevDistance1 = newDistance1;
    prevDistance2 = newDistance2;
  }

  delay(1000); // Delay for readability
}

// --- Function to Read a Single Ultrasonic Sensor ---
int readSingleUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);  // Wait for 2 microseconds
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); // Send 10 microseconds pulse
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);  // Read the pulse duration from ECHO pin
  int distance = duration * 0.0344 / 2;   // Calculate the distance (in cm)
  return distance;
}

// --- Function to Read Both Ultrasonic Sensors ---
void readUltrasonicSensors() {
  distance1 = readSingleUltrasonic(trigPin1, echoPin1);
  distance2 = readSingleUltrasonic(trigPin2, echoPin2);

  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.print(" cm  | Distance 2: ");
  Serial.println(distance2);
}
