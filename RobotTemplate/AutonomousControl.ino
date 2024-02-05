/*
  AutonomousControl.ino - Arduino Sketch for Autonomous Control of the RLSK robot

  State Machine description:
  The robot moves forward for a short time using a non-blocking delay, then
  the motors stop. Then the robot moves forward using the motor encoders

  Created by: Jennings Brooklyn, Rohan Malipeddi, Luis
  Date: Current Date
  Version: 1.0
*/

int wheelDiameterInches = 2.7559055;
int encoderResolution = 360;

void AutonomousControl(Servo mySero)
{

  unsigned long myTime;

  Serial.println("in the AutonomousControl function");

  // State machine loop
  while (AutoCurrentState != IDLE)
  {
    switch (AutoCurrentState)
    {
    case START:
      Serial.println("in Autonomous mode the current state: START");
      // Add START state instructions here
      AutoCurrentState = AUTO_ACTION1; // Transition to next state
      lastActionTime = millis();       // Record the time when the forward state started
      break;

    case AUTO_ACTION1:
      Serial.println("in Autonomous mode the current state: AUTO_ACTION1");
      // move forward for a time, then stop, and transition to the next state
      autonomousForward(20,10);
      AutoCurrentState = AUTO_ACTION2;
      break;

    case AUTO_ACTION2:
      Serial.println("in Autonomous mode the current state: AUTO_ACTION2");
      // Add state instructions here
      delay(200);       
                    // Placeholder delay
      autonomousSpinRight(10);
      AutoCurrentState = AUTO_ACTION3; // Transition to next state
      break;

    case AUTO_ACTION3:
      Serial.println("in Autonomous mode the current state: AUTO_ACTION3");
      // Add state instructions here
      delay(200);                     // Placeholder delay
      autonomousForward(20,10);
      AutoCurrentState = AUTO_ACTION4; // Transition to next state
      break;

    case AUTO_ACTION4:
      Serial.println("in Autonomous mode the current state: AUTO_ACTION4");
      // Add state instructions here
      delay(200);                     // Placeholder delay
      followLine(mySero);
      AutoCurrentState = AUTO_ACTION5; // Transition to next state
      break;
    
    case AUTO_ACTION5:
      Serial.println("in Autonomous mode the current state: AUTO_ACTION5");
      // Add state instructions here
      delay(1000);             // Placeholder delay
      AutoCurrentState = IDLE; // Transition to next state
      break;

    default:
      break;
    }
  }

  // The code will exit the while loop when IDLE state is reached
  Serial.println("State: IDLE");
  // Add IDLE state instructions here
  RobotCurrentState = MANUAL;    //switch to manual 
  AutoCurrentState = START;      //Set to start again to go into auto again
}

//function to keep track of the current count of the distance traveled by a point on the tip of the wheels
float distanceTraveled(uint8_t current_cnt)
{
  float temp = (wheelDiameterInches * PI * current_cnt) / encoderResolution;
  return temp;
}

//determines the encoder count that corresponds to an input distance
int countForDistance(uint32_t distance)
{
  float temp = (wheelDiameterInches * PI) / encoderResolution;
  temp = distance / temp;
  return int(temp);
}

//drives forward using the encoders until a target distance is achieved
void autonomousForward(float inchesToTravel, int speed)
{

  int totalCount = 0;
  int leftCount, rightCount;

  int target = countForDistance(inchesToTravel);
  /* Set the encoder pulses count back to zero */
  resetLeftEncoderCnt();
  resetRightEncoderCnt();

  /* Cause the robot to drive forward */
  setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);

  /* "Turn on" the motor */
  enableMotor(BOTH_MOTORS);



  /* Drive motor until it has received x encoder pulses */
  while (totalCount < target)
  {
    leftCount = getEncoderLeftCnt();
    rightCount = getEncoderRightCnt();
      /* Set motor speed */
    if(leftCount<rightCount){
      setMotorSpeed(LEFT_MOTOR, speed+0.02);
      setMotorSpeed(RIGHT_MOTOR,speed);
    }
    else if(rightCount<leftCount){
      setMotorSpeed(LEFT_MOTOR,speed);
      setMotorSpeed(RIGHT_MOTOR,speed+0.02);
    }
    else{
      setMotorSpeed(BOTH_MOTORS,speed);
    }
    totalCount = (leftCount + rightCount) / 2;
  }
  setMotorSpeed(BOTH_MOTORS, 0);

}

//use encoder to spin exactly  09 degrees left
void autonomousSpinLeft(int speed){

  int totalCount = 0;
  int leftCount, rightCount;

  int target = countForDistance(3);
  /* Set the encoder pulses count back to zero */
  resetLeftEncoderCnt();
  resetRightEncoderCnt();

  /* Cause the robot to drive forward */
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
  setMotorDirection(RIGHT_MOTOR,MOTOR_DIR_FORWARD);

  /* "Turn on" the motor */
  enableMotor(BOTH_MOTORS);

  /* Set motor speed */
  setMotorSpeed(BOTH_MOTORS, speed);

  /* Drive motor until it has received x pulses */
  while (totalCount <= target)
  {
    leftCount = getEncoderLeftCnt();
    rightCount = getEncoderRightCnt();
    totalCount = (leftCount + rightCount) / 2;
  }
  setMotorSpeed(BOTH_MOTORS, 0);
}

//use encoder to spin exactly  09 degrees right
void autonomousSpinRight(int speed){

  int totalCount = 0;
  int leftCount, rightCount;

  int target = countForDistance(3);
  /* Set the encoder pulses count back to zero */
  resetLeftEncoderCnt();
  resetRightEncoderCnt();

  /* Cause the robot to drive forward */
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD);
  setMotorDirection(RIGHT_MOTOR,MOTOR_DIR_BACKWARD);
  /* "Turn on" the motor */
  enableMotor(BOTH_MOTORS);

  /* Set motor speed */
  setMotorSpeed(BOTH_MOTORS, speed);

  /* Drive motor until it has received x pulses */
  while (totalCount <= target)
  {
    leftCount = getEncoderLeftCnt();
    rightCount = getEncoderRightCnt();
    totalCount = (leftCount + rightCount) / 2;
  }
  setMotorSpeed(BOTH_MOTORS, 0);
}