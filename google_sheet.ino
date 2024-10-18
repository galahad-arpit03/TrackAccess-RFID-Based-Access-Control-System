#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN  D3
#define SS_PIN   D4
#define BUZZER   D8

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;  
MFRC522::StatusCode status;      

int blockNum = 2;  
byte bufferLen = 18;
byte readBlockData[18];

String card_holder_name;
const String sheet_url = "https://script.google.com/macros/s/AKfycbzLKvIvMW7VGMuFiQDO5XYSpFLZkU5dT-2YFbvzUZr0a6KuoLxH9In37VnzXLqf1bhY/exec?name=";  

#define WIFI_SSID "Galahad"
#define WIFI_PASSWORD "whyarpit?"

LiquidCrystal_I2C lcd(0x3F, 8, 2);

void setup()
{
  Serial.begin(9600);
  lcd.begin(8,2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Initializing  ");
  for (int a = 5; a <= 10; a++) {
    lcd.setCursor(a, 1);
    lcd.print(".");
    delay(500);
  }
  
  Serial.println();
  Serial.print("Connecting to AP");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  pinMode(BUZZER, OUTPUT);
  SPI.begin();
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Scan your Card ");
  mfrc522.PCD_Init();
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) {return;}
  if ( ! mfrc522.PICC_ReadCardSerial()) {return;}

  Serial.println();
  Serial.println(F("Reading last data from RFID..."));
  ReadDataFromBlock(blockNum, readBlockData);

  Serial.println();
  Serial.print(F("Last data in RFID:"));
  Serial.print(blockNum);
  Serial.print(F(" --> "));
  for (int j=0 ; j<16 ; j++)
  {
    Serial.write(readBlockData[j]);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hey " + String((char*)readBlockData) + "!");
  }
  Serial.println();
  
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
  delay(200);
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
  
  if (WiFi.status() == WL_CONNECTED) {
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();

    card_holder_name = sheet_url + String((char*)readBlockData);
    card_holder_name.trim();
    Serial.println(card_holder_name);

    HTTPClient https;
    Serial.print(F("[HTTPS] begin...\n"));

    if (https.begin(*client, (String)card_holder_name)){
      Serial.print(F("[HTTPS] GET...\n"));
      int httpCode = https.GET();

      if (httpCode > 0) {
        Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        lcd.setCursor(0, 1);
        lcd.print(" Data Recorded ");
        delay(2000);
      }
      else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
      delay(1000);
    }
    else {
      Serial.printf("[HTTPS} Unable to connect\n");
    }
  }
}

void ReadDataFromBlock(int blockNum, byte readBlockData[]) 
{ 
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNum, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK){
     Serial.print("Authentication failed for Read: ");
     Serial.println(mfrc522.GetStatusCodeName(status));
     return;
  }

  Serial.println("Authentication success");

  status = mfrc522.MIFARE_Read(blockNum, readBlockData, &bufferLen);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("Reading failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  
  Serial.println("Block was read successfully");  
}
