#include <Servo.h>

void setup() {
  //Servos:
  Servo wheelServo;
  Servo armServo;
  Servo elbowServo;
  Servo clawServo;

  wheelServo.attach(...);//replace ... with appropriate pin number on arduino
  armServo.attach(...);
  elbowServo.attach(...);
  clawServo.attach(...);

  //DC Motors:


  //PixyCam:


  //IR Sensors:

  //Other
  bool rock_collected = False;
}

void pick_up_rock()
{

}

void rotate_rover()
{

}

void move()
{

}

float readPixyCam() //Not sure about the correct return type
{

}

float readIRSensors() //not sure about the correct return type
{

}

void loop() 
{
  // put your main code here, to run repeatedly:
  input = readPixyCam();
  if (...)
  {
    //can't locate rock -> rotate
    rotate_rover();
  }
  else if (...) //can see rock
  {
    //continue moving towards rock
    rotate_rover();
    move();
  }
  else if(...) //rock is right in front of us
  {
    //pick up rock
    pick_up_rock();
  }
  else if(...)// we have rock already
  {
    //move back to base
    rotate_rover();
    move();
  }
}
