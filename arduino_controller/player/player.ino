#include <Servo.h>

#define SERVO_PIN   12
#define SERVO_POWER 13
#define SERVO_LEFT  0
#define SERVO_RIGHT 180

#define LEFT_BUTTON  3
#define RIGHT_BUTTON   2

#define LEFT_VECTOR  1
#define RIGHT_VECTOR 0


enum go_to {
  left,
  right,
  _stop
};

volatile go_to go_to_current = _stop;
volatile int buttonState = 0;         // variable for reading the pushbutton status

Servo myservo;

void setup() {
  Serial.begin(9600);
  Serial.println("boot");
  
  myservo.attach(SERVO_PIN);
  pinMode(SERVO_POWER, OUTPUT);
  
  pinMode(RIGHT_BUTTON, INPUT);
  pinMode(LEFT_BUTTON, INPUT);

  attachInterrupt(RIGHT_VECTOR, right_int, CHANGE);
  attachInterrupt(LEFT_VECTOR, left_int, CHANGE);
}

void loop()
{
  delay(10);
}

void right_int()
{
  if (digitalRead(RIGHT_BUTTON))
  {
    digitalWrite(SERVO_POWER, HIGH);
    myservo.write(SERVO_RIGHT);
    Serial.println("Right button pressed");
  }
  else if (digitalRead(LEFT_BUTTON))
  {
    myservo.write(SERVO_LEFT);
  }
  else
  {
    digitalWrite(SERVO_POWER, LOW);
  }
}

void left_int()
{
  if (digitalRead(LEFT_BUTTON))
  {
    digitalWrite(SERVO_POWER, HIGH);
    myservo.write(SERVO_LEFT);
    Serial.println("Left button pressed");
  }
  else if (digitalRead(RIGHT_BUTTON))
  {
    myservo.write(SERVO_RIGHT);
  }
  else
  {
    digitalWrite(SERVO_POWER, LOW);
  }
}

