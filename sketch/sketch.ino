#include <Servo.h>
#include <SPI.h>
#include <Pixy2.h>

//set constants
//pin numbers
const int DC_DIRECTION = ...; //low = CW, high = CCW
const int DC_PWM = ...; // controls speed, 0 = not moving, max is 100
const int DC_BRAKE = ...; //set low to release brakes, high to activate brakes
const int WHEEL_SERVO_PIN = ...;
const int ARM_SERVO_PIN = ...;
const int CLAW_SERVO_PIN - ...;

//other constants
const int CLAW_CLOSED = ...;
const int CLAW_OPEN = ...;
const int ARM_UP = ...;
const int ARM_DOWN = ...;

//Initialize objects
Pixy2 pixy;

Servo wheelServo;
Servo armServo;
Servo elbowServo;
Servo clawServo;


void setup() {
  //Servos:
  wheelServo.attach(WHEEL_SERVO_PIN);//replace ... with appropriate pin number on arduino
  armServo.attach(ARM_SERVO_PIN);
  //elbowServo.attach(...); from my understanding we're not using this anymore
  clawServo.attach(CLAW_SERVO_PIN);

  //DC Motors:
  pinMode(DC_DIRECTION, OUTPUT);
  pinMode(DC_PWM, OUTPUT);
  pinMode(DC_BRAKE, OUTPUT);

  //PixyCam:


  //IR Sensors:

  //Other
  bool rock_collected = False;

  //set rover to inital state
  armServo.write(ARM_UP);
  clawServo.write(CLAW_OPEN);
}

void pick_up_rock()
{
  //servoObject.write(pos) sets the position of the servo (degrees), I think it should be between 0 and 180
  armServo.write(ARM_DOWN);
  delay(1000);//wait one second.. (may need to tune this to the actual amount of time it takes for servo to move down)
  clawServo.write(CLAW_CLOSED);
  delay(1000);
  armServo.write(ARM_UP); //I'm not sure if this is actually necessary
}

void rotate_rover(int degrees)
{
  //we might want to move the code that actually calculates how much to rotate it into here
  //but since we don't have any of that right now, I just set degrees as a parameter
  if (degrees >= 0 && degrees <= 180) //this probably depends on the servo, check with electronics or fabrication team
    wheelServo.write(degrees);
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
    bool success = pick_up_rock();
  }
  else if(...)// we have rock already
  {
    //move back to base
    rotate_rover();
    move();
  }
}
