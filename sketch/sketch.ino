#include <Servo.h>
#include <SPI.h>
#include <Pixy2.h>

//set constants
//pin numbers
DC_DIRECTION = ... //low = CW, high = CCW
DC_PWM = ... // controls speed, 0 = not moving, max is 100
DC_BRAKE = ... //set low to release brakes, high to activate brakes

//Initialize objects
Pixy2 pixy;

Servo wheelServo;
Servo armServo;
Servo elbowServo;
Servo clawServo;


void setup() {
  //Servos:
  wheelServo.attach(...);//replace ... with appropriate pin number on arduino
  armServo.attach(...);
  elbowServo.attach(...);
  clawServo.attach(...);

  //DC Motors:
  pinMode(DC_DIRECTION, OUTPUT);
  pinMode(DC_PWM, OUTPUT);
  pinMode(DC_BRAKE, OUTPUT);

  //PixyCam:


  //IR Sensors:

  //Other
  bool rock_collected = False;
}

void pick_up_rock()
{
  //servoObject.write(pos) sets the position of the servo (degrees), I think it should be between 0 and 180
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

bool readIRSensors() 
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
