/*
  TDC_Escaperoom
  light_rfid
  Ivar Nilsson
*/

#include "Arduino.h"
#include <Keypad.h>
#include <SPI.h>
//#include <LiquidCrystal.h>

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_1_PIN        10         // Configurable, take a unused pin, only HIGH/LOW required, must be different to SS 2

#define NR_OF_READERS   1

byte ssPins[] = {SS_1_PIN};

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.


char keys[3][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
};
byte rowPins[3] = {7, 6, 5}; // connect to the row pinouts of the keypad
byte colPins[3] = {4, 3, 2};   // connect to the column pinouts of the keypad
Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 3, 3);

//LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //Parameters: (rs, enable, d4, d5, d6, d7)

int LEDred = 1;
int LEDyellow = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting the RFID Reader...");

  // Initiating
   SPI.begin();        // Init SPI bus

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }

  //erial.println("go");

  //lcd.begin(16, 2); // LCD screen

  //lcd.clear();
  //lcd.print(" Access Control ");
  //lcd.setCursor(0, 1);
  //lcd.print("Scan Your Card>>");

  //pinMode(LEDyellow, OUTPUT);
  //pinMode(LEDred, OUTPUT);

}

void loop() {

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
      Serial.print(F("Reader "));
      Serial.print(reader);
      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F(": Card UID:"));
      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      Serial.println();
      Serial.print(F("PICC type: "));
      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/*
void loop() {

  digitalWrite(LEDyellow, LOW);
  digitalWrite(LEDred, LOW);

  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      //Serial.println(rfidCard + "   " + rfidCard.length());
    }
    rfid.halt();
  }

  char keyPressed = myKeypad.getKey();
  // If there is a character input, sent it to the serial port
  if (keyPressed) {
    //Serial.println(keyPressed);
    digitalWrite(LEDyellow, HIGH);
    digitalWrite(LEDred, HIGH);
  }

  delay(100);

}

*/