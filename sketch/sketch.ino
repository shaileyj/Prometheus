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
const int RECV_PIN = ...; // Pin number for the IR Sensor


//other constants
const int CLAW_CLOSED = ...;
const int CLAW_OPEN = ...;
const int ARM_UP = ...;
const int ARM_DOWN = ...;
const int CENTER_X = 158;
const int CENTER_Y = 104;

//IR Sensor value (default; nothing is there)
int objectVisible = LOW;

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

  digitalWrite(DC_BRAKE, LOW); //releasing the break
  digitalWrite(DC_PWM, 0); //initialize motor to 0 movement

  //PixyCam:
  Serial.begin(9600);
  pixy.init();

  //IR Sensors:
  pinMode(RECV_PIN, INPUT); // Input of the sensor


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

void move(int speed)
{
  digitalWrite(DC_BRAKE, LOW); // release brake
  digitalWrite(DC_DIRECTION, LOW);
  analogWrite(DC_PWM, speed);
}

void motorStop()
{
  analogWrite(DC_PWM, 0); // remove power
  digitalWrite(DC_BRAKE, HIGH); 


bool readIRSensors() 
{
  /*

  The return type here should be used in tandem with the PixyCam return type to identify objects.
  The IR Sensor will just tell you if an object is there. We need to use this function with the PixyCam to
  determine whether it is the object we want or not.

  */
  
  // Wait in between calling the command so the sensor runs in increments
  delay(500);
  // Read the sensor value
  objectVisible = digitalRead(RECV_PIN);
  if (objectVisible == HIGH){
    // Obstacle is detected
    return true;
  }
  else {
    // Continue to return false unless object is detected
    return false;
    // Turn the rover to look in another direction
  }
  delay(500);

}

int speed = 0;
int direction = 0;
int threshold = 10; //need to do some testing to find exact value, 
                    //this is the threshold of x pixels where if the center of the object is
                    //more than threshold pixels in the x direction away from the center of the
                    //image, we rotate
int rotation_rate = 2; //how fast we rotate when we need to adjust, also needs tuning

void loop() 
{
  // put your main code here, to run repeatedly:
<<<<<<< Updated upstream
  bool ir_input = readIRSensors(); // Data from IR Sensors
  int num_blocks = getBlocks(); //updates pixy data
  if() //rock is right in front of us (IR sensor detects rock?)
  {
    //pick up rock
    pick_up_rock();
    bool success = ...;
    if (!success)
    {
      readjust();
    }
  }
  else if (ir_input && num_blocks > 0) //can see rock ()
  {
    //continue moving towards rock
    int x = pixy.ccc.blocks[0].m_x;
    if (x > CENTER_X + threshold || x < CENTER_X - threshold)
    {   //rock is too far right   or    rock is too far left
      int rotation = (x-CENTER_X) * rotation_rate;
      rotate_rover(rotation);
      direction += rotation;
    }
    move(speed);
  }
  else if(...)// we have rock already
  {
    //move back to base
    rotate_rover();
    move();
  }
  else if ()
  {
    //can't locate rock in camera field of view -> rotate
    rotate_rover(...);
  }
}
