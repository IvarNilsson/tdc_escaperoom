/*
  TDC_Escaperoom
  blink_game
  Ivar Nilsson
  card: NodeMCU 1.0 (ESP-12E Module)
*/


int LEDgreen = D0;
int LEDblue = D1;
int LEDred = D3;

int BTNgreen = D8;
int BTNblue = D5;
int BTNyellow = D6;
int BTNred = D7;

int LEDdone = D4;

const int analogInPin = A0;

int order_size = 14;
int order[60] = {0, 1, 2, 3, 1, 3, 0, 2, 0, 3, 1, 3, 0, 1, 3, 2, 0, 1, 0, 2, 1, 0, 3, 0, 2, 0, 1, 0, 1, 0, 2, 3, 2, 3, 1, 0, 1, 2, 3};

int level = 1;

boolean level_compleate;
boolean done = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome");
  pinMode(LEDgreen, OUTPUT);
  pinMode(LEDblue, OUTPUT);
  pinMode(LEDred, OUTPUT);


  pinMode(BTNgreen, INPUT);
  pinMode(BTNblue, INPUT);
  pinMode(BTNyellow, INPUT);
  pinMode(BTNred, INPUT);

  pinMode(LEDdone, OUTPUT);

  rst();

  brown();
  for (int i = 0; i < 10000; i++) {
    digitalWrite(LEDdone, HIGH);
    delay(150);
    digitalWrite(LEDdone, LOW);
    delay(120);
  }
  delay(100000000);

}

// the loop function runs over and over again forever
void loop() {

  if (done) {
    off();
    brown();
    for (int i = 0; i < 10000; i++) {
      digitalWrite(LEDdone, HIGH);
      delay(150);
      digitalWrite(LEDdone, LOW);
      delay(120);
    }
    delay(100000000);
  }

  if (digitalRead(BTNgreen) == HIGH && digitalRead(BTNblue) == HIGH && digitalRead(BTNyellow) == HIGH && digitalRead(BTNred) == HIGH) {
    rst();
  } else {
    delay(1000);
    light_level(level);

    level_compleate = guess_level(level);

    if (level_compleate == true) {
      level ++;
      Serial.println(level);
    } else {
      rst();
      Serial.println(level);
    }

    if (level == order_size) {
      done = true;
    }

  }

}

void brown() {
  rgbLedDisplay(0, 0, 0);
}

void red() {
  rgbLedDisplay(0, 255, 255);
}
void green() {
  rgbLedDisplay(255, 0, 255);
}
void blue() {
  rgbLedDisplay(255, 255, 0);
}
void yellow() {
  rgbLedDisplay(0, 0, 255);
}
void off() {
  rgbLedDisplay(255, 255, 255);
}

void rgbLedDisplay(int red, int green, int blue) {
  // Set three ledPin to output the PWM duty cycle
  analogWrite(LEDred, constrain(red, 0, 255));
  analogWrite(LEDgreen, constrain(green, 0, 255));
  analogWrite(LEDblue, constrain(blue, 0, 255));
}

void rst() {
  off();
  level = 1;

  Serial.println("rst");
}

void light_level(int lv) {
  for (int i = 0; i < lv ; i ++) {
    if (order[i] == 0) {
      red();
    } else if (order[i] == 1) {
      green();
    } else if (order[i] == 2) {
      blue();
    } else if (order[i] == 3) {
      yellow();
    }
    delay(700);
    off();
    delay(100);
  }
}

boolean guess_level(int lv) {
  boolean right = true;
  for (int i = 0; i < lv; i++) {
    if (guess(i) == false) {
      Serial.println("fel!");
      return false;
    }
    Serial.println("rätt");
  }
  return true;
}

boolean guess(int order_nr) {
  boolean right_guesses = false;
  // 10 miljoner
  for (int i = 0; i < 1000; i++) {

    if (digitalRead(BTNred) == HIGH && order[order_nr] != 0) {
      Serial.println("FEL_röd");
      right_guesses = false;
      break;
    } else if (digitalRead(BTNgreen) == HIGH && order[order_nr] != 1) {
      Serial.println("FEL_grön");
      right_guesses = false;
      break;
    } else if (digitalRead(BTNblue) == HIGH && order[order_nr] != 2) {
      Serial.println("FEL_blå");
      right_guesses = false;
      break;
    } else if (digitalRead(BTNyellow) == HIGH && order[order_nr] != 3) {
      Serial.println("FEL_gul");
      right_guesses = false;
      break;
    }

    if (digitalRead(BTNred) == HIGH && order[order_nr] == 0) {
      Serial.println("RÄTT_röd");
      right_guesses = true;
      break;
    } else if (digitalRead(BTNgreen) == HIGH && order[order_nr] == 1) {
      Serial.println("RÄTT_grön");
      right_guesses = true;
      break;
    } else if (digitalRead(BTNblue) == HIGH && order[order_nr] == 2) {
      Serial.println("RÄTT_blå");
      right_guesses = true;
      break;
    } else if (digitalRead(BTNyellow) == HIGH && order[order_nr] == 3) {
      Serial.println("RÄTT_gul");
      right_guesses = true;
      break;
    }
    delay(10);
  }

  while (digitalRead(BTNred) == HIGH || digitalRead(BTNgreen) == HIGH || digitalRead(BTNblue) == HIGH || digitalRead(BTNyellow) == HIGH) {
    delay(10);
  }
  return right_guesses;
}