/*
  TDC_Escaperoom
  leds_outside_esp32
  ©Ivar Nilsson
  card: ESP32 (ESP32 Dev Module)
*/

#include <HTTPClient.h>
#include <WiFi.h>

// WiFi credentials
const char* ssid = "AASUS";
const char* password = "IvarNilsson/731";

int ledRed = 14;
int ledYellow = 27;

int btn = 34;

boolean transmitted = false;

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);

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

  digitalWrite(ledRed, HIGH);

}

void loop() {

  delay(250);
  
  if (digitalRead(btn) == HIGH) {
    writeF2();
    digitalWrite(ledRed, LOW);
    digitalWrite(ledYellow, HIGH);
  }

  if(transmitted == true){
    delay(10000000);
  }

  delay(250);
}

void writeF2() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://script.google.com/macros/s/AKfycbydSyxiUWwbKO6Roe26yosra6bV1KymxGhokLHnPt8XbowN29pdmJFksuYjcgeWjva3/exec?F2=1";
    Serial.println("Making a request");
    http.begin(url.c_str()); //Specify the URL and certificate
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();
    if (httpCode > 0) { //Check for the returning code
      Serial.println(httpCode);
      Serial.println("done");
      transmitted = true;
    }
    else {
      Serial.println("Error on HTTP request");
    }
    http.end();
  } else {
    Serial.println("FUUUUUUK");
  }
}