/*
  TDC_Escaperoom
  blink_game
  Ivar Nilsson
  card: NodeMCU 1.0 (ESP-12E Module)
*/

int buzzer = D6;
int led_green = D3;
int led_yellow = D1;
int led_red = D2;
int wrong_wire = D0;
int right_wire = D7;


void setup() {
  pinMode (buzzer, OUTPUT);
  pinMode (led_green, OUTPUT);
  pinMode (led_yellow, OUTPUT);
  pinMode (led_red, OUTPUT);

  pinMode (wrong_wire, INPUT);
  pinMode (right_wire, INPUT);
  Serial.begin(115200);
  Serial.println("START");
}

void loop() {

  if (digitalRead(wrong_wire) == HIGH && digitalRead(right_wire) == HIGH) {
    standbying();
    Serial.println("Standby");
  } else if (digitalRead(wrong_wire) == LOW) {
    Serial.println("BOOM");
    boom();
  } else if (digitalRead(right_wire) == LOW) {
    Serial.println("WIN");
    win();
  }

  delay(2000);
}

void standbying() {
  digitalWrite (buzzer, HIGH); //turn buzzer on
  digitalWrite( led_yellow, HIGH);
  delay(400);
  digitalWrite (buzzer, LOW);  //turn buzzer off
  digitalWrite( led_yellow, LOW);
}

void boom() {
  digitalWrite (buzzer, HIGH); //turn buzzer on
  digitalWrite( led_red, HIGH);
  delay(10000000);
}

void win() {
  digitalWrite (buzzer, HIGH); //turn buzzer on
  delay(100);
  digitalWrite (buzzer, LOW); //turn buzzer off
  delay(100);
  digitalWrite (buzzer, HIGH); //turn buzzer on
  delay(100);
  digitalWrite (buzzer, LOW); //turn buzzer off
  delay(100);
  digitalWrite (buzzer, HIGH); //turn buzzer on
  delay(100);
  digitalWrite (buzzer, LOW); //turn buzzer off
  delay(100);
  digitalWrite( led_green, HIGH);
  delay(10000000);
}