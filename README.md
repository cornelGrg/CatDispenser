# Cat Food Dispenser Project

## Overview
This project is an automated cat food dispenser that uses an ESP32 microcontroller to control servo motors, load cells (scales), and a vibration motor. The dispenser can be programmed to release a specific portion of food at scheduled times. It also includes a web server interface for configuration and monitoring.

## Hardware Requirements
- **MCU**: ESP32
- **Servo Motors**: 2 x Servo Motors
- **Load Cells**: 2 x HX711 (for scales)
- **Power Supply**: MB102
- **Vibration Motor**: 1 x Vibration Motor
- **Structure**: Cardboard, Glue, Tape, Wires, and Breadboard

## Software Requirements
- **Arduino IDE**: For programming the ESP32.
- **Libraries**:
  - `WiFi.h`
  - `AsyncTCP.h`
  - `ESPAsyncWebServer.h`
  - `LittleFS.h`
  - `ArduinoJson.h`
  - `HX711.h`
  - `Servo.h`
  - `HTTPClient.h`
  - `time.h`

## Project Layout

### Source Code Organization
The project is organized into several files, each handling a specific functionality:

- **wifiSupport.cpp**: Handles Wi-Fi connection and status checks.
- **CatDispenser.ino**: Main file that initializes the system and runs the state machine.
- **powerSaving.cpp**: Manages power-saving modes.
- **scaleSupport.cpp**: Handles calibration and reading of the load cells.
- **servoSupport.cpp**: Controls the servo motors.
- **stateMachine.cpp**: Implements the state machine logic for the dispenser.
- **webServerSupport.cpp**: Manages the web server for configuration and monitoring.
- **timerSupport.cpp**: Handles time synchronization and scheduling.

### How to Build, Burn, and Run the Project

1. **Install Arduino IDE**:
   - Download and install the Arduino IDE from [Arduino's official website](https://www.arduino.cc/en/software).

2. **Install Required Libraries**:
   - Open the Arduino IDE and go to `Sketch > Include Library > Manage Libraries`.
   - Search for and install the following libraries:
     - `WiFi`
     - `AsyncTCP`
     - `ESPAsyncWebServer`
     - `LittleFS`
     - `ArduinoJson`
     - `HX711`
     - `Servo`
     - `HTTPClient`
     - `time`

3. **Set Up the ESP32 Board**:
   - Go to `File > Preferences` and add the following URL to the "Additional Boards Manager URLs":
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   - Go to `Tools > Board > Boards Manager`, search for `ESP32`, and install the `esp32` package by Espressif Systems.

4. **Select the Board and Port**:
   - Go to `Tools > Board` and select `ESP32 Dev Module`.
   - Go to `Tools > Port` and select the port where your ESP32 is connected.

5. **Load the Project**:
   - Open the `CatDispenser.ino` file in the Arduino IDE.
   - Ensure all other `.cpp` and `.h` files are in the same directory.

6. **Compile and Upload**:
   - Click the `Verify` button (checkmark) to compile the code.
   - Click the `Upload` button (right arrow) to burn the code to the ESP32.

7. **Run the Project**:
   - Once the code is uploaded, the ESP32 will start running the cat food dispenser program.
   - Connect to the Wi-Fi network and access the web server interface to configure the dispenser.

## User Guide

1. **Initial Setup**:
   - Power on the ESP32 and ensure it is connected to your Wi-Fi network.
   - Access the web server interface by navigating to the ESP32's IP address in a web browser.

2. **Configure Dispenser**:
   - Set the portion size and dispense times using the web interface.
   - Save the settings, and the dispenser will start operating according to the schedule.

3. **Monitor and Control**:
   - Use the web interface to monitor the current state of the dispenser (e.g., standby, dispensing, refill needed).
   - Manually trigger dispensing if needed.

4. **Refill Notification**:
   - When the dispenser needs a refill, it will send a notification via Telegram and display an alert on the web interface.

## Links
- **PowerPoint Presentation**: [Link to your PowerPoint presentation]
- **YouTube Video**: [Link to your YouTube video]

## Conclusion
This project provides an automated solution for dispensing cat food at scheduled times, with remote monitoring and control capabilities. It is a great example of how IoT can be used to simplify everyday tasks.
