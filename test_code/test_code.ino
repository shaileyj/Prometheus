const int CENTER_X = 158;
const int CENTER_Y = 104;

//necessary variables
int speed = 0;
int direction = 0;
int threshold = 10; //need to do some testing to find exact value, 
                    //this is the threshold of x pixels where if the center of the object is
                    //more than threshold pixels in the x direction away from the center of the
                    //image, we rotate
float rotation_rate = 0.05; //how fast we rotate when we need to adjust, also needs tuning
bool success = false;

//mock inputs
int mock_pixy_x = 158;
int mock_num_blocks = 1;
bool mock_ir_input = true;
int sim_steps = 2;
bool mock_success = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Hello World!");

  Serial.println("Enter simulated steps:");
  while(!Serial.available()){}
  sim_steps = Serial.parseInt();
}

bool pick_up_rock()
{
  Serial.println("Called pick_up_rock");
  return mock_success;
}

void rotate_rover(int degrees)
{
  Serial.print("Called rotate_rover with angle of ");
  Serial.println(degrees);
}

void move(int speed)
{
  Serial.print("Called move with speed of ");
  Serial.println(speed);
}

void motorStop()
{
  Serial.println("Called motorStop");
}

bool readIRSensors() 
{
  Serial.print("Called readIRSensors and read ");
  Serial.println(mock_ir_input, BIN);
  return mock_ir_input;
}

void search_for_rock() 
{
  Serial.println("Called search_for_rock");
  rotate_rover(90);  // scanning environment for rock
  move(80);  // low speed?
  //delay(500);
// in case the pixycam needs time to process, we may need to set a delay
  motorStop();
  //delay(200);
  Serial.println("Finished search_for_rock call");
}

void readjust()
{
  Serial.println("Called readjust");
  // Assuming that this means that the rock is in range but missed
  rotate_rover(1); // chose this value randomly. ideally should be smaller movement than rotate_rover() to fine tune
  // should we also move backwards a bit?
  pick_up_rock();
  Serial.println("Finished readjust");
}

void loop() 
{
  if (sim_steps > 0)
  {
    Serial.print("Remaining steps: ");
    Serial.println(sim_steps);
    Serial.print("Speed: ");
    Serial.println(speed);
    Serial.print("Direction: ");
    Serial.println(direction);
    Serial.print("Success: ");
    Serial.println(success);

    Serial.print("Enter mock_pixy_x: ");
    while(!Serial.available()){}
    mock_pixy_x = Serial.parseInt();
    Serial.println(mock_pixy_x);
    Serial.print("Enter mock_num_blocks: ");
    while(!Serial.available()){}
    mock_num_blocks = Serial.parseInt();
    Serial.println(mock_num_blocks);
    Serial.print("Enter mock_ir_input: ");
    while(!Serial.available()){}
    mock_ir_input = Serial.parseInt() != 0;
    Serial.println(mock_ir_input);
    Serial.print("Enter mock_success: ");
    while(!Serial.available()){}
    mock_success = Serial.parseInt() != 0;
    Serial.println(mock_success);

    // put your main code here, to run repeatedly:
    bool ir_input = readIRSensors(); // Data from IR Sensors
    int num_blocks = mock_num_blocks; //updates pixy data
    int x = mock_pixy_x;

    if(success)// we have rock already
    {
      //move back to base
      rotate_rover(rotation_rate);
      move(speed);
    }

    //rock is right in front of us (Pixy and IR both detect rock)
    else if(ir_input && num_blocks > 0 && (x <= CENTER_X + threshold || x >= CENTER_X - threshold)) 
    {
      //modified to only pick up if the rock is within range and detected by sensor
      //pick up rock
      motorStop();
      success = pick_up_rock();
      if (!success)
      {
        readjust();
      }
    }

    else if (!ir_input && num_blocks > 0) //can see rock (only Pixy detects rock, IR doesn't)
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

    else if (!ir_input && num_blocks == 0) //rock is not detected by Pixy or IR sensors (need to spin to see it)
    {
      //can't locate rock in camera field of view -> rotate
      search_for_rock();
    }
    sim_steps--;
  }
}