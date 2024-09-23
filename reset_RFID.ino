#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>

// Define pins for MFRC522
#define RST_PIN  D3
#define SS_PIN   D4

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
MFRC522::MIFARE_Key key;          // Key for authentication
MFRC522::StatusCode status;       // Status code for MFRC522 operations

// Block number to clear
int blockNum = 2;
byte bufferLen = 16; // Block size is 16 bytes
byte clearData[16] = {0}; // Data to write (clearing block by writing zeros)

#define WIFI_SSID ""  // Wifi Name
#define WIFI_PASSWORD "" // Wifi Password

void setup() {
  Serial.begin(9600);

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  Serial.println("\nWiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize SPI bus and MFRC522 module
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  // Check for new card
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // Reset (clear) data from the block
  Serial.println("Clearing data from RFID...");
  ResetBlock(blockNum, clearData);

  Serial.println("Data cleared successfully.");
  delay(2000); // Wait before next loop iteration
}

void ResetBlock(int blockNum, byte newData[]) {
  // Prepare the key for authentication
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  // Authenticate the block
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Authentication failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  // Write new data to the block
  status = mfrc522.MIFARE_Write(blockNum, newData, bufferLen);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Writing failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  Serial.println("Block was written successfully");
}
