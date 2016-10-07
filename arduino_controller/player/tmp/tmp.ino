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
  left = 0,
  right = 180,
  _stop = 90
};

volatile go_to go_to_current = _stop;
volatile go_to go_to_prev = _stop;
volatile int rightButtonState = LOW;         // variable for reading the pushbutton status
volatile int leftButtonState = LOW;         // variable for reading the pushbutton status

Servo myservo;

void setup() {
  Serial.begin(9600);
  
  myservo.attach(SERVO_PIN);
  pinMode(SERVO_POWER, OUTPUT);
  
  pinMode(RIGHT_BUTTON, INPUT);
  pinMode(LEFT_BUTTON, INPUT);

  attachInterrupt(RIGHT_VECTOR, rightPin_ISR, CHANGE);
  attachInterrupt(LEFT_VECTOR, leftPin_ISR, CHANGE);
}

void loop()
{
}

void executeMove(go_to action)
{
  if (action == _stop || (leftButtonState == LOW && rightButtonState == LOW))
  {
   digitalWrite(SERVO_POWER, LOW);
  }
  else
  {
   digitalWrite(SERVO_POWER, HIGH);
   myservo.write(action);
  }
}

void rightPin_ISR() {
  rightButtonState = digitalRead(RIGHT_BUTTON);
  Serial.print("Right button status:");
  Serial.println(rightButtonState, DEC);
  if (rightButtonState == HIGH)
    {
      go_to_prev = go_to_current;
      go_to_current = right;
      executeMove(go_to_current);
    }
  else
    {
      go_to_current = go_to_prev;
      executeMove(go_to_current);
    }
}

void leftPin_ISR() {
  leftButtonState = digitalRead(LEFT_BUTTON);
  Serial.print("Left button status:");
  Serial.println(leftButtonState, DEC);
  if (leftButtonState == HIGH)
    {
      go_to_prev = go_to_current;
      go_to_current = left;
      executeMove(go_to_current);
    }
  else
    {
      go_to_current = go_to_prev;
      executeMove(go_to_current);
    }
}
