/*
  TDC_Escaperoom
  leds_inside_esp32
  ©Ivar Nilsson
  card: ESP32 (ESP32 Dev Module)
*/

#include <HTTPClient.h>
#include <WiFi.h>

// WiFi credentials
const char* ssid = "";
const char* password = "";

int ledRed = 14;
int ledYellow1 = 27;
int ledYellow2 = 26;
int ledGreen = 25;

int btn = 34;

int buzzer = 33;

boolean reciveOn = false;
boolean opend = false;

String recived;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow1, OUTPUT);
  pinMode(ledYellow2, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(btn, INPUT);

  delay(1000);
  Serial.begin(115200);
  delay(1000);
  // connect to WiFi
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  Serial.flush();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

}

void loop() {
  digitalWrite(ledYellow1, LOW);
  if (digitalRead(btn) == HIGH) {
    digitalWrite(ledYellow1, HIGH);
  }

  if (opend == true) {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow1, LOW);
    digitalWrite(ledYellow2, LOW);
    digitalWrite(ledGreen, HIGH);
  } else {
    if (reciveOn == true) {
      digitalWrite(buzzer, HIGH);
      delay(400);
      digitalWrite(buzzer, LOW);
      delay(1000);
      if (digitalRead(btn) == HIGH) {
        digitalWrite(ledGreen, HIGH);
        opend = true;
        // skicka till utsidan?
        delay(500);
      }
    } else {
      recived = readF2();
      if (recived.equalsIgnoreCase("1")) {
        reciveOn = true;
        digitalWrite(ledYellow2, HIGH);
      }
    }
  }
  delay(100);
}

String readF2() {
  String payload;
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "";
    Serial.println("Making a request");
    http.begin(url.c_str()); //Specify the URL and certificate
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();
    if (httpCode > 0) { //Check for the returning code
      payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
    }
    else {
      Serial.println("Error on HTTP request");
    }
    http.end();
  } else {
    Serial.println("FUUUUUUK");
  }
  return payload;
}