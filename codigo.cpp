const int led1 = 2;
const int led2 = 5;
const int led3 = 8;
const int led4 = 10;
const int led5 = 12;

const int button1 = 3;
const int button2 = 6;
const int button3 = 9;
const int button4 = 11;
const int button5 = 13;

int leds[] = {led1, led2, led3, led4, led5};
bool ledOn[] = {true, true, true, true, true};
int buttons[] = {button1, button2, button3, button4, button5};
int numLeds = sizeof(leds) / sizeof(leds[0]);
int bombLed = -1;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
    pinMode(buttons[i], INPUT);
  }
  randomSeed(analogRead(0));
  bombLed = random(numLeds); 
  Serial.println(bombLed);
}

void loop() {
  if (digitalRead(buttons[bombLed]) == HIGH) {
    loser();
    loser();
    loser(); 
    resetGame();
    delay(500);
  }

  for (int i = 0; i < numLeds; i++) {
    if (i != bombLed) {
      if (digitalRead(buttons[i])) {
        digitalWrite(leds[i], LOW);
        ledOn[i]=false;
        delay(300);
      }
      
    }
    if (isWin()) {
      celebrate();
      delay(200);
      celebrate();
      delay(200);
      celebrate();
      resetGame();
      delay(500);
    }
  
    
  }
}

bool isWin() {
  for(int i=0; i < numLeds; i++) {
    if(i != bombLed && ledOn[i] == true) {
      return false;
    }
  }
  
  return true;
}

void celebrate() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], HIGH);
    delay(100);
  }
  for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(leds[i], LOW);
    delay(100);
  }
}

void loser() {
  digitalWrite(leds[0], LOW);
  digitalWrite(leds[1], LOW);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[3], LOW);
  digitalWrite(leds[4], LOW);
  delay(125);
  digitalWrite(leds[0], HIGH);
  digitalWrite(leds[1], HIGH);
  digitalWrite(leds[2], HIGH);
  digitalWrite(leds[3], HIGH);
  digitalWrite(leds[4], HIGH);
  delay(125);
}

void resetGame() {
  bombLed = random(numLeds);
  Serial.println(bombLed);
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], HIGH);
    ledOn[i] = true;
  }
}
