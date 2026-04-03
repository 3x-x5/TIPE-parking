# Parking Management System - Laptop Interface Version

## Overview
This version uses your **laptop's Serial Monitor** as the display interface instead of a physical LCD screen. All parking data, car detection events, and system status are shown directly on your computer screen.

## Hardware Setup

### Components Needed:
- Arduino Uno R3
- 2x Ultrasonic Sensors (HC-SR04)
- 2x LEDs (Green and Red)
- 2x 220Ω resistors for LEDs
- Jumper wires
- USB cable to connect Arduino to laptop

### Wiring Diagram:

#### Ultrasonic Sensors:
**Entrance Sensor:**
- VCC → 5V
- GND → GND
- TRIG → Pin 7
- ECHO → Pin 8

**Exit Sensor:**
- VCC → 5V
- GND → GND
- TRIG → Pin 9
- ECHO → Pin 10

#### LEDs:
**Green LED (Available):**
- Anode (+) → Pin 11 (through 220Ω resistor)
- Cathode (-) → GND

**Red LED (Full):**
- Anode (+) → Pin 12 (through 220Ω resistor)
- Cathode (-) → GND

## Software Instructions

### Step 1: Upload Code
1. Open Arduino IDE
2. Open the file `parking_laptop_interface.ino`
3. Select your Arduino board (Tools → Board → Arduino Uno)
4. Select the correct port (Tools → Port)
5. Click Upload

### Step 2: Open Serial Monitor
1. After upload completes, click the **Serial Monitor** icon (magnifying glass) in Arduino IDE
2. Set baud rate to **9600** (dropdown at bottom of Serial Monitor)
3. You should see the initialization message

## What You'll See on Screen

### Initialization:
```
========================================
   PARKING MANAGEMENT SYSTEM
   Interface: Laptop (Serial Monitor)
========================================

Systeme initialise avec succes!
Capacite totale: 3 places
```

### When Car Enters:
```
----------------------------------------
>>> Voiture DETECTEE A L'ENTREE
>>> Place attribuee!

=== STATUS DU PARKING ===
Places disponibles: 2/3
Places occupees: 1
Status: DISPONIBLE [LED VERTE ON]
===========================
```

### When Parking is Full:
```
----------------------------------------
>>> Voiture A L'ENTREE mais PARKING PLEIN!
>>> Acces refuse!

=== STATUS DU PARKING ===
Places disponibles: 0/3
Places occupees: 3
Status: COMPLET [LED ROUGE ON]
===========================
```

### When Car Exits:
```
----------------------------------------
>>> Voiture DETECTEE A LA SORTIE
>>> Place liberee!

=== STATUS DU PARKING ===
Places disponibles: 1/3
Places occupees: 2
Status: DISPONIBLE [LED VERTE ON]
===========================
```

## Features

✅ **No LCD wiring needed** - Simplified setup
✅ **Real-time monitoring** - See all events as they happen
✅ **Better debugging** - Detailed logs on your computer
✅ **Visual indicators** - Green/Red LEDs still work on hardware
✅ **Capacity tracking** - Automatically counts cars in/out
✅ **Full parking alert** - Notifies when no spaces available

## Troubleshooting

**No output in Serial Monitor?**
- Check baud rate is set to 9600
- Ensure USB cable is properly connected
- Try closing and reopening Serial Monitor

**Sensors not detecting cars?**
- Verify wiring matches the diagram above
- Test each sensor individually
- Check that objects are within 20cm range

**LEDs not working?**
- Check polarity (long leg is positive)
- Verify resistor connections
- Test with simple blink example first

## Next Steps

You can enhance this project by:
- Adding RFID access control
- Implementing servo motor for barrier gate
- Creating a graphical interface with Python
- Logging data to a file
- Adding WiFi/Bluetooth connectivity

---
**Created:** April 2025  
**Directory:** `/workspace/made by ai/`  
**Version:** Laptop Interface (No LCD)
