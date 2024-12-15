# Sensing the FREEdge

## Project Overview

Sensing the FREEdge is an Arduino-based project inspired by the "Sensing the City" community fridge initiative. This project utilizes sensors to monitor a fridge's interior environment and detects changes when the door is opened or closed. The aim is to provide real-time feedback about food placement within the fridge using ultrasonic sensors, a temperature and humidity sensor, and a door magnet sensor.

This repository includes:
- Debugging code to test individual sensor functionality.
- Live code for the fully integrated system.

## Features

- **Ultrasonic Sensors**: Detect changes in distance to monitor food placement or removal.
- **DHT11 Sensor**: Measure temperature and humidity inside the fridge.
- **Door Magnet Sensor**: Detect when the fridge door is opened or closed to trigger sensor readings.

## Components

### Hardware

- **Arduino**: The central microcontroller running the system.
- **Ultrasonic Sensors (x2)**: Measure distance to detect food placement.
  - **Connections**:
    - Sensor 1: TRIG → D11, ECHO → D10
    - Sensor 2: TRIG → D8, ECHO → D9
- **DHT11 Sensor**: Measures temperature and humidity.
  - **Connection**: SIGNAL → D3
- **Gikfun MC-38 Door Magnet Sensor**: Detects door open/close state.
  - **Connection**: One wire to D7, one to the negative rail.
- **Breadboard**: Organizes connections.
- **Jumper Wires**: Connect components to the Arduino.

### Software

- **Arduino IDE**: Used to write and upload the code.

## Code

### Debugging Code

The debugging code ensures that each sensor is correctly connected and outputs accurate readings.

#### Features:
- Individual sensor testing (temperature, humidity, door state, ultrasonic distances).
- Outputs results to the Serial Monitor for verification.

#### Code Snippet:
```cpp
#include <DHT.h>

const int dhtPin = 3;        // Pin connected to the DHT11 data pin
const int trigPin = 11;      // Pin connected to ultrasonic sensor TRIG
const int echoPin = 10;      // Pin connected to ultrasonic sensor ECHO
const int doorSensorPin = 7; // Pin connected to the reed switch (door sensor)

DHT dht(dhtPin, DHT11);      // Initialize DHT11 sensor

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(doorSensorPin, INPUT_PULLUP);
}

void loop() {
  // Add sensor debugging code here...
}

```

### Live Code

The live code integrates all sensors to detect and report fridge activity in real time. When the door opens, the ultrasonic sensors report distance readings to detect food placement changes. Additionally, temperature and humidity readings are logged.

#### Key Functions:
- **Ultrasonic Sensors**: Measure distance and compare against baseline readings to determine if food was added/removed.
- **DHT11 Sensor**: Measure and report fridge temperature and humidity.
- **Door Sensor**: Trigger data collection when the door is opened.

#### Code Snippet:
```cpp
#include <DHT.h>

const int dhtPin = 3;        // Pin connected to the DHT11 data pin
const int trigPin1 = 11;     // Pin connected to ultrasonic sensor 1 TRIG
const int echoPin1 = 10;     // Pin connected to ultrasonic sensor 1 ECHO
const int trigPin2 = 8;      // Pin connected to ultrasonic sensor 2 TRIG
const int echoPin2 = 9;      // Pin connected to ultrasonic sensor 2 ECHO
const int doorSensorPin = 7; // Pin connected to the reed switch (door sensor)

DHT dht(dhtPin, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(doorSensorPin, INPUT_PULLUP);
}

void loop() {
  // Add live sensor integration code here...
}

```

