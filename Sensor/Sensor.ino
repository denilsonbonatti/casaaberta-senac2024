#include <Ultrasonic.h>

int red = 10;
int yellow = 11;
int green = 12;

Ultrasonic ultrasonic(4, 5);

int distance;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  distance = ultrasonic.read();
  
  Serial.print("Distancia em CM: ");
  Serial.println(distance);

  if (distance>10) {
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, HIGH);
  }

  if (distance<10 && distance>5) {
    digitalWrite(red, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(green, LOW);
  }

  if (distance<=5) {
    digitalWrite(red, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
  }
  
  
  delay(500);

}
