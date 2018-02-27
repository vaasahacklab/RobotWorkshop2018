
#include <Servo.h>
#include <NewPing.h>

#define MOTOR1_PIN1 4
#define MOTOR1_PIN2 5

#define MOTOR2_PIN1 6
#define MOTOR2_PIN2 7

#define TRIG 8
#define ECHO 9
#define MAX_DISTANCE 200

#define SERVO 12

const int THRESHOLD = 15;

NewPing sonar(TRIG, ECHO, MAX_DISTANCE);
Servo servo;

void setup(){
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  pinMode(SERVO, OUTPUT);
  
  servo.attach(SERVO);
  
}

void loop(){
  int distance = measureDistance();
  delay(100);
  
  while(distance >= THRESHOLD) {
    forward();
    int dist0 = measureDistance();
    delay(100);
    turnServo(60);
    delay(100);
    int dist1 = measureDistance();
    delay(100);
    turnServo(120);
    delay(100);
    int dist2 = measureDistance();
    delay(100);
    turnServo(90);
    delay(100);
    distance = min(dist0, dist1);
    distance = min(distance, dist2);
  }
  stopMovement();
  
  turnServo(0);
  delay(300);
  int rightDistance = measureDistance();
  turnServo(180);
  delay(600);
  int leftDistance = measureDistance();
  turnServo(90);
  if(leftDistance > rightDistance)
    turnLeft();
  else
    turnRight();
  delay(500);
  turnServo(90);
}

int measureDistance(){
  int distance = sonar.ping_cm();
  if(distance == 0) return MAX_DISTANCE;
  return distance;
}

void turnServo(int val){
  servo.write(val);
}

void forward(){
  rightMotorForward();
  leftMotorForward();
}

void backward(){
  rightMotorBackward();
  leftMotorBackward();
}

void turnLeft(){
  rightMotorForward();
  leftMotorBackward();
}

void turnRight(){
  rightMotorBackward();
  leftMotorForward();
}

void stopMovement(){
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, LOW);
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, LOW);
}

void rightMotorForward(){
  digitalWrite(MOTOR1_PIN1, HIGH);
  digitalWrite(MOTOR1_PIN2, LOW);
}

void rightMotorBackward() {
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, HIGH);
}

void leftMotorForward(){
  digitalWrite(MOTOR2_PIN1, HIGH);
  digitalWrite(MOTOR2_PIN2, LOW);
}

void leftMotorBackward(){
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, HIGH);
}


