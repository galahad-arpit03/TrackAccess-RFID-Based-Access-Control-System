#Trackaccess
# RFID-Based Data Clearing System with WiFi Connectivity

## Overview

This project is a system that uses an **ESP8266 microcontroller** and the **MFRC522 RFID module** to read and clear data on an RFID tag via a WiFi connection. When a valid RFID card is detected, the system authenticates the card and clears a predefined block of data on the card. It also connects to a WiFi network for remote monitoring or integration with a cloud service.

### Features:
- **RFID Card Detection**: Detects and reads RFID cards.
- **Data Clearing**: Clears specific blocks of data on the RFID card.
- **WiFi Connectivity**: Connects to a WiFi network and prints the IP address.
- **Security**: Uses the default authentication key `0xFF` for interaction with the RFID card.

---

## Hardware Requirements

- **ESP8266 Module (e.g., NodeMCU)**: A WiFi-enabled microcontroller.
- **MFRC522 RFID Module**: Used for reading and writing RFID cards.
- **RFID Cards/Tags**: Cards that support the MIFARE protocol.
- **Jumper Wires**: For connecting the ESP8266 to the RFID module.
- **Power Supply**: Suitable for powering both the ESP8266 and the RFID module.

---

## Software Requirements

- **Arduino IDE**: The Integrated Development Environment for programming the ESP8266.
- **ESP8266 Board Support**: Install the ESP8266 board package in the Arduino IDE.
- **MFRC522 Library**: For interacting with the MFRC522 RFID module.
- **ESP8266WiFi Library**: For enabling WiFi functionality on the ESP8266.

---

## Functionality

### 1. **WiFi Connection**
- Connects to a specified WiFi network using the `ESP8266WiFi` library. Once connected, it prints the IP address to the serial monitor.

### 2. **RFID Card Detection**
- The system detects an RFID card and reads its serial number.

### 3. **Authentication and Data Clearing**
- The system authenticates the RFID card using a predefined key (`0xFF`), then clears the data from a specific block (Block 2 in this case).

### 4. **Serial Feedback**
- After the data clearing process, the system prints success or failure messages to the serial monitor.

---

## Project Setup

### Wiring Connections

1. **ESP8266 to MFRC522**:
   - **VCC** -> 3.3V
   - **GND** -> GND
   - **SDA (SS)** -> D4
   - **SCK** -> D5
   - **MOSI** -> D7
   - **MISO** -> D6
   - **RST** -> D3

2. **Power Supply**:
   - Ensure both the **ESP8266** and **MFRC522** are powered with a stable 3.3V supply.

---

## How It Works

1. **Startup**:
   - Upon powering up, the system initializes the **MFRC522 RFID module** and connects to the specified WiFi network.

2. **Card Detection**:
   - The system continuously checks for RFID cards. When a card is detected, it reads the card’s serial number.

3. **Data Clearing**:
   - After successful authentication, the system clears data from Block 2 of the card by writing zeros to that block.

4. **WiFi Status**:
   - The system prints the WiFi connection status and IP address to the serial monitor, allowing for easy monitoring and debugging.

---

## Usage Instructions

### 1. Upload the Code
- Open the **Arduino IDE** and upload the code to the ESP8266. Make sure to select the correct board and port.

### 2. Connect to WiFi
- Enter your WiFi credentials (SSID and password) in the code before uploading it to the ESP8266. The module will connect to your WiFi network.

### 3. Monitor the Serial Output
- Open the serial monitor in the Arduino IDE to view the WiFi connection status and RFID card interactions.

### 4. RFID Card Interaction
- Place an RFID card in front of the **MFRC522 reader**. The system will authenticate and clear the data from the specified block.

---

## Enhancements

- **Enhanced Security**: Implement dynamic key management or unique keys per card instead of using the default `0xFF`.
- **Cloud Integration**: Send card interaction logs to a cloud platform for remote access and monitoring.
- **Error Handling**: Improve error handling by retrying on authentication or writing failures.
- **Multiple Block Clearing**: Extend the functionality to clear multiple blocks or support more operations like reading or updating card data.

