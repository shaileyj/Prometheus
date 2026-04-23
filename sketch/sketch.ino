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
const int ARM_TEST = ...;
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


void search_for_rock() 
{
  rotate_rover(90);  // scanning environment for rock

  move(80);  // low speed?

  delay(500);

// in case the pixycam needs time to process, we may need to set a delay
  motorStop();
  delay(200);
}


void pick_up_rock()
{
  //servoObject.write(pos) sets the position of the servo (degrees), I think it should be between 0 and 180
  float no_rock_time = 0;
  float rock_time = 0;

  armServo.write(ARM_DOWN);
  delay(1000);//wait one second.. (may need to tune this to the actual amount of time it takes for servo to move down)
  clawServo.write(CLAW_CLOSED);
  delay(1000);
  armServo.write(ARM_UP); //I'm not sure if this is actually necessary
<<<<<<< Updated upstream
=======
  return true; // Check if the rock is actually picked up before hard-coding bool value as true (REVISE!)

  // Arm Down all the way
  // Arm up to test degree value (measure elapsed time)
  // Claw opens
  // Tries to pick up rock
  // Lift to test degree value and measure this elapsed time
  // check with pixy cam at test degree value to see if the rock is detected (signature)
  // if elapsed time 2 > elapsed time 1, then the rock was picked up and return true
  // else, keep trying to pick up the rock 

  // try to figure out a way to 'jiggle' the rock so it stays in the claw
>>>>>>> Stashed changes

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


float readPixyCam() //Not sure about the correct return type
{
  int num_blocks = getBlocks();
  for(int i=0; i < num_blocks; i++)
    if (pixy.ccc.blocks[i].m_index == tracking_index)
    {
      return pixy.ccc.blocks[i].
    }
}

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


void readjust()
{
  // Assuming that this means that the rock is in range but missed
  rotate_rover(1); // chose this value randomly. ideally should be smaller movement than rotate_rover() to fine tune
  // should we also move backwards a bit?
  pick_up_rock();
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
  int x = pixy.ccc.blocks[0].m_x;
  bool ir_input = readIRSensors();
  int pixy_data = readPixyCam();

  if (pixy_data == -1) // search mode if no rock has been detected
  {
    search_for_rock();
  }

  
  if(ir_input && (x <= CENTER_X + threshold || x >= CENTER_X - threshold)) //rock is right in front of us (IR sensor detects rock?)
  {
    //modified to only pick up if the rock is within range and detected by sensor
    //pick up rock
    motorStop();
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
  else if (ir_input && num_blocks == 0) //rock is not detected in field of vision
  {
    //can't locate rock in camera field of view -> rotate
      rotate_rover(...); 
  }
}
