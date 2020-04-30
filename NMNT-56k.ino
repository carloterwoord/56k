#include <Servo.h>

Servo servOne;
Servo servTwo;

int buzzer = 14; //D5
int sensor = 12; //D6
int servo1 = 16; //D0
int servo2 = 5; //D1

int led1 = 4; //D2
int led2 = 0; //D3
int led3 = 2; //D4

int pos = 0;

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  servOne.attach(servo1);
  servTwo.attach(servo2);
}

//Main loop
void loop() {
  long state = digitalRead(sensor);
  delay(1000);
  if (state == HIGH) {
    Serial.println("Motion detected!");
    ledSequence(10, 100);
    delay(500);
    kTone();
    
    for (int x = 0; x < 10; x++) {
      servoMove();
    }

    ledSequence(10, 100);
    ledOff();
    
    delay(5000);
  }
  else {
    Serial.println("Motion absent!");
    ledOff();
    servOne.write(0);
    servTwo.write(0);
    noTone(buzzer);
    
    delay(15000);
    ledSequence(1, 100);
    
    for (int x = 0; x < 2; x++) {
      servoMove();
    }
    
    ledOff();
    delay(10000);
  }
}

// Blinking LEDs
void ledSequence(int repeat, int delTime) {
  for (int i = 0; i < repeat; i++) {
    ledOff();
    delay(delTime);
    ledOn();
    delay(delTime);
  }
}

// Servo movement
void servoMove() {
  for (pos = 0; pos <= 180; pos += 10) {
    servOne.write(pos);
    servTwo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 10) {
    servOne.write(pos);
    servTwo.write(pos);
    delay(15);
  }
}

// 56k Modem tone
void kTone() {
  tone(buzzer, 3300);
  delay(50);
  tone(buzzer, 300);
  delay(50);
  tone(buzzer, 3000);
  delay(100);
  tone(buzzer, 3300);
  delay(500);
  tone(buzzer, 3000);
  delay(500);
  tone(buzzer, 1000);
  delay(1000);
  tone(buzzer, 330);
  delay(1500);
  tone(buzzer, 3300);
  delay(50);
  tone(buzzer, 300);
  delay(50);
  tone(buzzer, 660);
  delay(3000);
  tone(buzzer, 300);
  delay(50);
  tone(buzzer, 600);
  delay(3000);
  tone(buzzer, 300);
  delay(2000);
  tone(buzzer, 100);
  delay(1000);
  tone(buzzer, 200);
  delay(500);
  tone(buzzer, 100);
  noTone(buzzer);
}

void ledOff() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
}

void ledOn() {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
}
