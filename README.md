# TrackAccess---RFID-Based-Access-Control-System-
This project is an RFID-based access control system using NodeMCU ESP8266. It logs user entries into a Google Sheet in real-time, improving security in areas like offices or labs. The system uses RFID tags, provides feedback via an LCD display and buzzer, and ensures seamless tracking with Wi-Fi connectivity for accurate digital records.

# RFID-Based Access Control System

This project is an RFID-based access control system that uses the **NodeMCU ESP8266** to log entries into important areas like offices, labs, or cabins. It improves security by keeping a real-time digital record of every entry, which is stored in **Google Sheets**.

## Features
- **RFID Scanning**: Logs user entries using RFID cards.
- **Google Sheets Integration**: Stores entry logs in real-time on Google Sheets for easy tracking.
- **Wi-Fi Connectivity**: Sends data to Google Sheets via Wi-Fi.
- **User Feedback**: LCD display and buzzer provide instant feedback on successful or failed scans.

## Components Used
- **NodeMCU ESP8266**
- **RC522 RFID Reader**
- **16x2 I2C LCD Display**
- **RFID Tags**
- **Buzzer**
- **Breadboard & Jumper Wires**

## How It Works
1. **Initialization**: The system sets up the RFID reader, Wi-Fi connection, and LCD display.
2. **RFID Tag Scan**: When an RFID card is scanned, the system reads the unique ID from the tag.
3. **Data Logging**: The system sends the ID to a **Google Sheet** using HTTP requests.
4. **Feedback**: The LCD displays the scan status, and the buzzer indicates a successful or failed scan.

## Installation
1. Clone the repository:
   ```bash
   https://github.com/galahad-arpit03/TrackAccess-RFID-Based-Access-Control-System
   ```
3. Install the required libraries:
   - **ESP8266WiFi.h** (for Wi-Fi connection)
   - **MFRC522.h** (for RFID reader)
   - **HTTPClient.h** (for HTTP requests)
4. Flash the code onto the **NodeMCU ESP8266** board.
5. Set up the Google Sheets script to receive HTTP GET requests.

## Usage
1. Power up the system.
2. Scan an RFID tag; the system will display the result on the LCD.
3. The entry will be logged in the connected Google Sheets for tracking.

## Contributing
Feel free to submit issues or pull requests if you'd like to contribute to this project.
