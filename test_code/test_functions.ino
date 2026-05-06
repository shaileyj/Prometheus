#include <Servo.h>
#include <Pixy2.h>

Pixy2 pixy;

// set up pins
const int DC_DIRECTION = ;
const int DC_PWM = ;
const int DC_BRAKE = ;

const int WHEEL_SERVO_PIN = ;
const int ARM_SERVO_PIN = ;
const int CLAW_SERVO_PIN = ;

const int RECV_PIN = ;


Servo wheelServo;
Servo armServo;
Servo clawServo;

void setup() {
  Serial.begin(9600);

  
  pinMode(DC_DIRECTION, OUTPUT);
  pinMode(DC_PWM, OUTPUT);
  pinMode(DC_BRAKE, OUTPUT);

  // ir sensor
  pinMode(RECV_PIN, INPUT);


  wheelServo.attach(WHEEL_SERVO_PIN);
  armServo.attach(ARM_SERVO_PIN);
  clawServo.attach(CLAW_SERVO_PIN);


  pixy.init();

  Serial.println("=== Rover Hardware Test Start ===");
}

void loop() {
  testMotor();
  testServos();
  testIR();
  testPixy();

  delay(3000);
}

// motor test
void testMotor() {

  digitalWrite(DC_BRAKE, LOW);
  digitalWrite(DC_DIRECTION, LOW);

  analogWrite(DC_PWM, 150);
  delay(2000);

  analogWrite(DC_PWM, 0);
  digitalWrite(DC_BRAKE, HIGH);

}

// serv test
void testServos() {

  // double check if this is how servos steer
  wheelServo.write(0);
  delay(1000);
  wheelServo.write(90);
  delay(1000);
  wheelServo.write(180);
  delay(1000);

  armServo.write(0);
  delay(1000);
  armServo.write(90);
  delay(1000);


  clawServo.write(0);
  delay(1000);
  clawServo.write(90);
  delay(1000);

}

// ir sensor 

void testIR() {

  int val = digitalRead(RECV_PIN);

  if (val == HIGH) {
    Serial.println("object");
  } else {
    Serial.println("no object");
  }
}


void testPixy() {

  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks) {
    Serial.print("detected blocks");
    Serial.println(pixy.ccc.numBlocks);

    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      Serial.print("X: ");
      Serial.print(pixy.ccc.blocks[i].m_x);
      Serial.print("color signature");
      Serial.println(pixy.ccc.blocks[i].m_signature);
    }
  } else {
    Serial.println("nothing detected");
  }
}
