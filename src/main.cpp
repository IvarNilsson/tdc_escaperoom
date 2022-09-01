/*
  TDC_Escaperoom
  light_rfid
  Ivar Nilsson
*/

#include "Arduino.h"
#include <Keypad.h>
#include <SPI.h>
#include <RFID.h>
//#include <LiquidCrystal.h>
    
#define RST_PIN 9
#define SS_PIN 10

String rfidCard;

char keys[3][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
};

byte rowPins[3] = {7, 6, 5}; // connect to the row pinouts of the keypad
byte colPins[3] = {4, 3, 2};   // connect to the column pinouts of the keypad

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 3, 3);

RFID rfid(SS_PIN, RST_PIN);
//LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //Parameters: (rs, enable, d4, d5, d6, d7)

int LEDred = 1;
int LEDyellow = 0;

void setup() {
  //Serial.begin(9600);
  //Serial.println("Starting the RFID Reader...");

  // Initiating
  SPI.begin(); // SPI bus
  rfid.init();

  //erial.println("go");

  //lcd.begin(16, 2); // LCD screen

  //lcd.clear();
  //lcd.print(" Access Control ");
  //lcd.setCursor(0, 1);
  //lcd.print("Scan Your Card>>");

  pinMode(LEDyellow, OUTPUT);
  pinMode(LEDred, OUTPUT);

}

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