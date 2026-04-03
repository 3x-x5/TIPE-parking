/*
 * Basic Parking System - Laptop Interface Only
 * 
 * Components:
 * - Arduino Uno
 * - 2 Ultrasonic Sensors (HC-SR04): Entry & Exit
 * - 2 LEDs: Red (Full) & Green (Available)
 * - Laptop Screen (Serial Monitor)
 * 
 * Wiring:
 * ----------
 * Entry Sensor (HC-SR04):
 *   VCC -> 5V
 *   GND -> GND
 *   TRIG -> Pin 2
 *   ECHO -> Pin 3
 * 
 * Exit Sensor (HC-SR04):
 *   VCC -> 5V
 *   GND -> GND
 *   TRIG -> Pin 4
 *   ECHO -> Pin 5
 * 
 * Green LED (Available):
 *   Anode (+) -> Pin 6 (via 220Ω resistor)
 *   Cathode (-) -> GND
 * 
 * Red LED (Full):
 *   Anode (+) -> Pin 7 (via 220Ω resistor)
 *   Cathode (-) -> GND
 */

// Pin Definitions
const int ENTRY_TRIG = 2;
const int ENTRY_ECHO = 3;
const int EXIT_TRIG = 4;
const int EXIT_ECHO = 5;
const int LED_GREEN = 6;
const int LED_RED = 7;

// Parking Configuration
const int MAX_CAPACITY = 3;
int currentCars = 0;

// Timing Constants
const long SENSOR_TIMEOUT = 10000; // 10ms timeout for sensor reading
const int DEBOUNCE_DELAY = 1000;   // 1 second debounce to prevent double counting

// State Variables
bool entrySensorActive = false;
bool exitSensorActive = false;
unsigned long lastEntryTime = 0;
unsigned long lastExitTime = 0;

void setup() {
  // Initialize Serial Communication
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for Serial port to connect
  }
  
  // Initialize Pins
  pinMode(ENTRY_TRIG, OUTPUT);
  pinMode(ENTRY_ECHO, INPUT);
  pinMode(EXIT_TRIG, OUTPUT);
  pinMode(EXIT_ECHO, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // Initial State
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_RED, LOW);
  
  Serial.println("========================================");
  Serial.println("  BASIC PARKING SYSTEM - LAPTOP MODE");
  Serial.println("========================================");
  Serial.print("Maximum Capacity: ");
  Serial.println(MAX_CAPACITY);
  Serial.println("System Ready...");
  Serial.println("----------------------------------------");
  updateDisplay();
}

void loop() {
  // Check Entry Sensor
  checkEntrySensor();
  
  // Check Exit Sensor
  checkExitSensor();
  
  // Update LED indicators
  updateLEDs();
  
  // Small delay to prevent overwhelming the system
  delay(100);
}

void checkEntrySensor() {
  long duration = readSensor(ENTRY_TRIG, ENTRY_ECHO);
  bool carDetected = (duration > 0 && duration < SENSOR_TIMEOUT);
  
  if (carDetected && !entrySensorActive) {
    // Car just entered detection zone
    entrySensorActive = true;
    lastEntryTime = millis();
  } else if (!carDetected && entrySensorActive) {
    // Car has passed through
    if (millis() - lastEntryTime > DEBOUNCE_DELAY) {
      if (currentCars < MAX_CAPACITY) {
        currentCars++;
        Serial.println("[ENTRY] Car detected! Count increased.");
        updateDisplay();
      } else {
        Serial.println("[ENTRY] Car detected but parking is FULL!");
      }
      entrySensorActive = false;
    }
  }
}

void checkExitSensor() {
  long duration = readSensor(EXIT_TRIG, EXIT_ECHO);
  bool carDetected = (duration > 0 && duration < SENSOR_TIMEOUT);
  
  if (carDetected && !exitSensorActive) {
    // Car just entered detection zone
    exitSensorActive = true;
    lastExitTime = millis();
  } else if (!carDetected && exitSensorActive) {
    // Car has passed through
    if (millis() - lastExitTime > DEBOUNCE_DELAY) {
      if (currentCars > 0) {
        currentCars--;
        Serial.println("[EXIT] Car detected! Count decreased.");
        updateDisplay();
      }
      exitSensorActive = false;
    }
  }
}

long readSensor(int trigPin, int echoPin) {
  // Clear the trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Send 10us pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read echo with timeout
  long duration = pulseIn(echoPin, HIGH, SENSOR_TIMEOUT);
  
  return duration;
}

void updateLEDs() {
  if (currentCars >= MAX_CAPACITY) {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
  } else {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  }
}

void updateDisplay() {
  int available = MAX_CAPACITY - currentCars;
  
  Serial.println("----------------------------------------");
  Serial.print("Current Cars: ");
  Serial.print(currentCars);
  Serial.print(" / ");
  Serial.println(MAX_CAPACITY);
  Serial.print("Available Spots: ");
  Serial.println(available);
  
  if (available > 0) {
    Serial.println("Status: AVAILABLE (Green LED ON)");
  } else {
    Serial.println("Status: FULL (Red LED ON)");
  }
  Serial.println("----------------------------------------");
}
