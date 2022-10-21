/*
  TDC_Escaperoom
  tdc_core
  Ivar Nilsson
  card: arduino UNO
*/

#include <Keypad.h>
#include <SPI.h>
#include <RFID.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9
#define SS_PIN 10

char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte rowPins[4] = {7, 6, 5, 4}; // connect to the row pinouts of the keypad
byte colPins[4] = {3, 2, 1, 0};   // connect to the column pinouts of the keypad

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

RFID rfid(SS_PIN, RST_PIN);

LiquidCrystal_I2C lcd(0x27, 16, 2);

String rfidCard;
String key;

int stage = 2;

int light_sensor = A3;
int adcValue;
float voltage;

byte BigOwithDots[8] = {  //Ö
  0b01010,
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};

byte AwithDots[8] = {  //ä
  B01010,
  B00000,
  B01110,
  B00001,
  B01111,
  B10001,
  B01111,
};

String O = "Ö";
String a = "ä";

void setup() {
  pinMode(light_sensor, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  SPI.begin(); // SPI bus
  rfid.init();

  lcd.createChar(6, BigOwithDots);
  lcd.createChar(2, AwithDots);
  O.replace("Ö", "\6");
  a.replace("ä", "\2");
  lcd.clear();
  stage2();
}

void loop() {

  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
    }
    rfid.halt();
  }


  if (rfidCard.equalsIgnoreCase("67 43 80 167")) {
    stage0();
  }

  if (rfidCard.equalsIgnoreCase("115 48 77 144") && stage > 0) {
    stage1();
  }

  adcValue = analogRead(light_sensor);
  voltage = adcValue * (5.0 / 1023.0);
  if (voltage > 4.8 && stage > 1) {
    stage2();
  }


  char keyPressed = myKeypad.getKey();
  if (keyPressed) {
    if (keyPressed == '*') {
      if (key.equalsIgnoreCase("*7041") && stage > 2) {
        stage3();
      } else {
        key = "*";
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(key);
      }
    } else {
      key = key + String(keyPressed);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(key);
    }
  }



  delay(200);
}

void stage0() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Quack Quack");
  lcd.setCursor(5, 1);
  lcd.print("Quack Quack");
  if (stage == 0) {
    stage = 1;
  }
  rfidCard = " ";
}

void stage1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vilka batteri " + a + "r");
  lcd.setCursor(0, 1);
  lcd.print("i minir" + a + "knaren?");
  if (stage == 1) {
    stage = 2;
  }
  rfidCard = " ";
}

void stage2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NADIR");
  lcd.setCursor(0, 1);
  lcd.print("s.195");
  if (stage == 2) {
    stage = 3;
  }
}

void stage3() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("101 " + O + "L");
  lcd.setCursor(0, 1);
  lcd.print("s.137");
  if (stage == 3) {
    stage = 4;
  }
}