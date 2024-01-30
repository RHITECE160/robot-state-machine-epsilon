/*Epsilon Final project code 
  A template for the final project code that uses multiple files
  for modularity. The compiler first loads the principal file 
  (the one with the same name as the folder) and then loads 
  the others in alphabetical order. Variables defined in an 
  earlier file will be visible to code in a file that is loaded 
  later, but not vice-versa. 

  Calls functions in files:
  AutonomousControl.ino
  MotorFunctions.ino
  RemoteControl.ino

  written for the MSP432401 board
  Author: Walter Deborah, Jennings Brooklyn, Rohan Malipeddi, Luis Hernandez
  Last revised: 1/23/2024

***** Hardware Connections: *****
     start button       P3.0
     
     playstation connections
     brown wire         P1.7 
     orange wire        P1.6 
     yellow wire        P2.3
     blue wire          P6.7
*/

// Load libraries used
#include "SimpleRSLK.h"
#include <Servo.h>
#include "PS2X_lib.h"

// Define pin numbers for the button on the PlayStation controller
#define PS2_DAT 14  //P1.7 <-> brown wire
#define PS2_CMD 15  //P1.6 <-> orange wire
#define PS2_SEL 34  //P2.3 <-> yellow wire (also called attention)
#define PS2_CLK 35  //P6.7 <-> blue wire
#define START_BUTTON 18  //P3.0 a push button on top of the breadboard

// Create an instance of the playstation controller object
PS2X ps2x;
Servo myServo;

// Define high-level state machine
enum RobotState {
  INITIALIZE,
  MANUAL,
  AUTONOMOUS,
  LINEFOLLOWING
};

// Define lower-level state machine for AUTONOMOUS mode
enum AutoState {
  START,
  AUTO_ACTION1,
  AUTO_ACTION2,
  AUTO_ACTION3,
  AUTO_ACTION4,
  AUTO_ACTION5,
  IDLE
};

// Declare and initialize the current state variable
RobotState RobotCurrentState = INITIALIZE;
AutoState AutoCurrentState = START;

// Global Variables
unsigned long lastActionTime = 0;  // Variable to store the last time an action was taken

// Tuning Parameters
const uint16_t lowSpeed = 15;
const uint16_t fastSpeed = 20;
const unsigned long movementDuration = 2000;  // Duration for movement forward autonomously in milliseconds

const int servoPin = 38;

bool isCalibrationComplete = false;

void setup() {
  Serial.begin(57600);
  Serial.print("Starting up Robot code...... ");

  // Run setup code
  setupRSLK();
  myServo.attach(servoPin);

  // Initialize PlayStation controller
  delayMicroseconds(500 * 1000);  //added delay to give wireless ps2 module some time to startup, before configuring it
  // declare variables for playstation control
  bool pressures = false;
  bool rumble = false;
  int error = 1;

  while (error) {
    error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);

    if (error == 0)
      Serial.print("Found Controller, configured successful ");

    else if (error == 1)
      Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

    else if (error == 2)
      Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if (error == 3)
      Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
    delayMicroseconds(1000 * 1000);
  }

  // set pushbutton on breadboard to use internal pullup resistor
  pinMode(START_BUTTON, INPUT_PULLUP);

  setupWaitBtn(START_BUTTON);
  delay(1000);

  setupLed(RED_LED);

  if (isCalibrationComplete == false) {
        floorCalibration();
        isCalibrationComplete = true;
  }

}

void loop() {
  // Read input from PlayStation controller
  ps2x.read_gamepad();

  // Update state machine based on button input
  updateStateMachine();

  // Perform actions based on the current state
  executeStateActions();
}

/* updateStateMachine function
  This function changes the high-level state based on user input. 
  
  For an example, a SPST button (using internal pullup resistor) is used
  to change state from INITIALIZE to MANUAL. The playstation circle 
  button is used to change the state from MANUAL to AUTONOMOUS.
*/
/*
-> Goes into manual state when button on breadboard is pressed
-> Circle pressed goes into autonomous
-> while in autonomous, if square is pressed, it goes into line following
-> wihle in line following, if triangle is pressed, goes into manual
      -> also sets the AutoCurrentState to be Start
*/
void updateStateMachine() {
  switch (RobotCurrentState) {
    case INITIALIZE:
      if (digitalRead(START_BUTTON) == 0) {
        Serial.print("start button has been pressed going to manual");
        //go to Manual state when start button pushed
        RobotCurrentState = MANUAL;
      }
      break;

    case MANUAL:
      Serial.print("in manual state........");
      if (ps2x.Button(PSB_CIRCLE)) {
        // go to Autonomous state when circle button pushed
        Serial.print("Circle pressed going to auto........");
        RobotCurrentState = AUTONOMOUS;
      }
      break;

    case AUTONOMOUS:
      Serial.print("in autonomous state........");
      if (ps2x.Button(PSB_SQUARE)) {
        // go to manual state when square button pushed
        Serial.print("square pressed going to manual.......");
        RobotCurrentState = MANUAL;
      }
      break;

    // case LINEFOLLOWING:
    //   Serial.print("in line following state........");
    //   if(ps2x.Button(PSB_TRIANGLE)) {
    //     //go to Line following mode when triangle pressed
    //     Serial.print("traingle pressed going to manual.......");
    //     RobotCurrentState = MANUAL;
    //     // reset autonomous state to start state for the next time
    //     AutoCurrentState = START;
    //   }

    //   break;
  }
}

/* executeStateActions function
  This function executes the proper actions for each state. 
  
  For an example, two functions are called, RemoteControl and 
  AutonomousControl. These functions are located in their respective
  files to make the code easier to read and modify.
*/
void executeStateActions() {
  switch (RobotCurrentState) {
    case INITIALIZE:
      // Perform actions for the initialize state
      Serial.println("Initializing...");
      // Add any additional actions for the initialize state
      break;

    case AUTONOMOUS:
      // Perform actions for the autonomous state
      Serial.println("Autonomous Mode");
      AutonomousControl(myServo);
      // Add any additional actions for the autonomous state
      break;

    case MANUAL:
      // Perform actions for the manual state
      Serial.println("Manual Mode");
      RemoteControl(ps2x, myServo);
      // Add any additional actions for the manual state
      break;

    // case LINEFOLLOWING:
    //   //Performs line following based on controller input
    //   Serial.print("Line Following mode");
    //   followLine(ps2x, myServo);
    //   break;
  }
}
