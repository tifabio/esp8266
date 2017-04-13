int redPin = D2, greenPin = D3, isObstaclePin = D8;
int isObstacle = HIGH;  // HIGH MEANS NO OBSTACLE

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  isObstacle = digitalRead(isObstaclePin);
  if (isObstacle == LOW) // OBSTACLE
  {
    digitalWrite(greenPin, LOW);   
    digitalWrite(redPin, HIGH);   
  }
  else
  {
    digitalWrite(redPin, LOW);   
    digitalWrite(greenPin, HIGH);
  }
  delay(100);
}
