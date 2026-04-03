# Basic Parking System

A simplified automated parking system using only essential components with laptop monitoring.

## Components Needed
- Arduino Uno
- 2 × HC-SR04 Ultrasonic Sensors (Entry & Exit)
- 1 × Green LED (Available indicator)
- 1 × Red LED (Full indicator)
- 2 × 220Ω Resistors (for LEDs)
- Jumper wires
- Breadboard

## Wiring Diagram

### Entry Sensor (HC-SR04)
```
Sensor Pin → Arduino Pin
VCC        → 5V
GND        → GND
TRIG       → Pin 2
ECHO       → Pin 3
```

### Exit Sensor (HC-SR04)
```
Sensor Pin → Arduino Pin
VCC        → 5V
GND        → GND
TRIG       → Pin 4
ECHO       → Pin 5
```

### Green LED (Available)
```
LED Leg    → Arduino Pin
Anode (+)  → Pin 6 (via 220Ω resistor)
Cathode (-)→ GND
```

### Red LED (Full)
```
LED Leg    → Arduino Pin
Anode (+)  → Pin 7 (via 220Ω resistor)
Cathode (-)→ GND
```

## How It Works

1. **Entry Detection**: When a car passes the entry sensor, the count increases (if space available)
2. **Exit Detection**: When a car passes the exit sensor, the count decreases
3. **LED Indicators**:
   - **Green LED ON**: Parking spaces available
   - **Red LED ON**: Parking is full
4. **Laptop Monitor**: Real-time status displayed in Serial Monitor

## Setup Instructions

1. **Connect Hardware**: Wire all components according to the diagram above
2. **Upload Code**: 
   - Open `basic_parking.ino` in Arduino IDE
   - Select your Arduino board and port
   - Click Upload
3. **Open Serial Monitor**:
   - Click the magnifying glass icon (or Tools → Serial Monitor)
   - Set baud rate to **9600**
   - You'll see real-time parking status

## Sample Output

```
========================================
  BASIC PARKING SYSTEM - LAPTOP MODE
========================================
Maximum Capacity: 3
System Ready...
----------------------------------------
----------------------------------------
Current Cars: 0 / 3
Available Spots: 3
Status: AVAILABLE (Green LED ON)
----------------------------------------

[ENTRY] Car detected! Count increased.
----------------------------------------
Current Cars: 1 / 3
Available Spots: 2
Status: AVAILABLE (Green LED ON)
----------------------------------------

[ENTRY] Car detected! Count increased.
----------------------------------------
Current Cars: 2 / 3
Available Spots: 1
Status: AVAILABLE (Green LED ON)
----------------------------------------

[ENTRY] Car detected! Count increased.
----------------------------------------
Current Cars: 3 / 3
Available Spots: 0
Status: FULL (Red LED ON)
----------------------------------------

[EXIT] Car detected! Count decreased.
----------------------------------------
Current Cars: 2 / 3
Available Spots: 1
Status: AVAILABLE (Green LED ON)
----------------------------------------
```

## Features

✅ **No LCD Required** - Uses laptop screen via Serial Monitor  
✅ **Simple Wiring** - Only 8 pins used on Arduino  
✅ **Debouncing** - Prevents double-counting cars  
✅ **Visual Feedback** - Red/Green LEDs show status at a glance  
✅ **Real-time Logging** - See every entry/exit event  

## Troubleshooting

| Problem | Solution |
|---------|----------|
| No output in Serial Monitor | Check baud rate is set to 9600 |
| LEDs not lighting | Check polarity and 220Ω resistors |
| Sensors not detecting | Verify TRIG/ECHO wiring, check 5V power |
| Double counting cars | Increase DEBOUNCE_DELAY in code |
| False detections | Adjust sensor positioning or add physical barriers |

## Customization

- **Change Capacity**: Modify `MAX_CAPACITY` value (line 20)
- **Adjust Sensitivity**: Change `DEBOUNCE_DELAY` (line 24)
- **Different Pins**: Update pin definitions at the top of the code

---
**Created for**: Simplified parking system demonstration  
**Interface**: Laptop Serial Monitor only (no LCD)
