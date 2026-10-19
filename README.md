# Smart Fall Detection System

An IoT-based prototype that detects potential falls using an ESP8266 NodeMCU and an MPU6050 motion sensor.

## Project Overview

The system monitors acceleration data and looks for a low-acceleration event followed by a high-impact event within a defined time window. When a potential fall is detected, it activates an LED and buzzer and displays an alert on an LCD.

## Features

- Motion monitoring using the MPU6050 accelerometer and gyroscope.
- Threshold-based potential fall detection.
- Audible and visual alerts using a buzzer and LED.
- Real-time status messages on a 16×2 I²C LCD.
- Wi-Fi connection attempt using the ESP8266.

## Hardware Components

- ESP8266 NodeMCU
- MPU6050 accelerometer and gyroscope
- 16×2 I²C LCD, address `0x27`
- LED
- Buzzer
- Jumper wires and a suitable power supply

## Pin Connections

| Component | ESP8266 Pin |
|---|---|
| LCD SDA | D1 |
| LCD SCL | D2 |
| LED | D6 |
| Buzzer | D7 |

## Software and Libraries

- Arduino IDE
- ESP8266 board support package
- Adafruit MPU6050
- Adafruit Unified Sensor
- LiquidCrystal I²C
- Wire
- ESP8266 Wi-Fi

## Getting Started

1. Install Arduino IDE and the ESP8266 board support package.
2. Install the required libraries.
3. Connect the components according to the pin table.
4. Configure your Wi-Fi credentials locally if Wi-Fi connectivity is required.
5. Open `SmartFallDetection.ino`, select your ESP8266 board and port, then upload the sketch.

**Security:** Never commit real Wi-Fi passwords, API keys, or Telegram bot tokens to a public repository.

## Current Limitations

- Detection uses fixed acceleration thresholds and may miss falls or produce false alarms.
- The current sketch does not send Telegram notifications.
- Wi-Fi connectivity is attempted, but fall detection is processed locally.
- The prototype has not been validated for medical or safety-critical use.

## Future Improvements

- Add secure remote notifications.
- Improve fall detection using more robust sensor analysis.
- Test detection accuracy under different movement conditions.
- Add circuit diagrams and project demonstration photos.

## Disclaimer

This project is intended for educational and prototyping purposes only. It should not be relied upon as a medical device or safety-critical alert system.

## Author

Mutemi Mary, Computer Science student: Internet of Things Enthusiast.
