/*
 * Energia Robot Library for Texas Instruments' Robot System Learning Kit (RSLK)
 * Line Following Example
 *
 * Summary:
 * This example has the TI Robotic System Learning Kit (TI RSLK) follow a line
 * using a basic line following algorithm. This example works on a dark floor with
 * a white line, but may be changed by modifying the _lineColor_ value. The robot 
 * first needs to be calibrated (on floor without line). Then place the robot
 * on the line and hit the left button again to begin the line following.
 *
 * How to run:
 * 1) Place the robot on floor away from line to calibrate to background surface.
 * 2) Push left button on Launchpad to have the robot perform calibration.
 * 3) Place the robot center on the line you want it to follow.
 * 4) Push left button again to have the robot begin to follow the line.
 *
 * Parts Info:
 * o Black eletrical tape or white electrical tape. Masking tape does not work well
 *   with IR sensors.
 *
 * Learn more about the classes, variables and functions used in this library by going to:
 * https://ndroid.github.io/msp432-core/RSLK/
 *
 * Learn more about the TI RSLK by going to http://www.ti.com/rslk
 *
 * created by Franklin Cooper Jr.
 * modified by chris miller 
 *
 * This example code is in the public domain.
 */

/* Include RSLK library */
//#include "SimpleRSLK.h"

/* Modify the following line to use an alternate UART interface (i.e. Serial1/2/3) */
#define UART_SERIAL Serial

/* Valid values are either:
 *  DARK_LINE  if your floor is lighter than your line
 *  LIGHT_LINE if your floor is darker than your line
 */
const uint8_t lineColor = LIGHT_LINE;
const uint16_t normalSpeed = 10;

PS2X Controller;

// modified the example to use a button on the breadboard not side
#define START_BUTTON 18  //P3.0 a push button on top of the breadboard

void floorCalibration()
{
    /* Place Robot On Floor (no line) */
    delay(2000);
    //UART_SERIAL.println("Push left button on Launchpad to begin calibration.");
    //UART_SERIAL.println("Make sure the robot is on the floor away from the line.\n");

    Serial.println("Push left button on Launchpad to begin calibration.");
    Serial.println("Make sure the robot is on the floor away from the line.\n");
    /* Wait until button is pressed to start robot */
    /* Wait until button is pressed to start robot */
    waitBtnPressed(START_BUTTON, RED_LED);

    delay(500);
    //UART_SERIAL.println("Running calibration on floor");
    Serial.println("Running calibration on floor");
    /* Set both motors direction forward */
    setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
    /* Enable both motors */
    enableMotor(BOTH_MOTORS);
    /* Set both motors speed 20 */
    setMotorSpeed(BOTH_MOTORS, 20);

    /* Must be called prior to using getLinePosition() or readCalLineSensor() */
    calibrateLineSensor(lineColor);

    /* Disable both motors */
    disableMotor(BOTH_MOTORS);

    //UART_SERIAL.println("Reading floor values complete");
    Serial.println("Reading floor values complete");

    //UART_SERIAL.println("Push START button on Breadboard to begin line following.");
    //UART_SERIAL.println("Make sure the robot is on the line.\n");
    Serial.println("Push START button on Breadboard to begin line following.");
    Serial.println("Make sure the robot is on the line.\n");
    /* Wait until button is pressed to start robot */
    waitBtnPressed(START_BUTTON, RED_LED);
    delay(1000);

    enableMotor(BOTH_MOTORS);
}

//bool isCalibrationComplete = false;
void followLine(PS2X ps2, Servo myServo)
{
    /* Run this setup only once */
    // if (isCalibrationComplete == false) {
    //     Controller = ps2;
    //     floorCalibration();
    //     isCalibrationComplete = true;
    // }

    bool follow = true;
    while(follow) {
      uint32_t linePos = getLinePosition();
      Serial.println(linePos);
      if ((linePos > 0) && (linePos < 4000)) {    // turn left
          setMotorSpeed(LEFT_MOTOR, normalSpeed);
          setMotorSpeed(RIGHT_MOTOR, fastSpeed);
      } else if (linePos > 5000) {                // turn right
          setMotorSpeed(LEFT_MOTOR, fastSpeed);
          setMotorSpeed(RIGHT_MOTOR, normalSpeed);
      } else {                                    // go straight
          setMotorSpeed(LEFT_MOTOR, normalSpeed);
          setMotorSpeed(RIGHT_MOTOR, normalSpeed);
      }
      ps2.read_gamepad();
      if(ps2.Button(PSB_PAD_UP)) {
        follow = false;
      }
    }
    Openclaw(myServo);
    Serial.print("Line Following stopped");
}

// void findLine() {
//   uint32_t linePos = getLinePosition();
//   Serial.println(linePos);
//   while(linePos == 0) {
//     spinSlow();
//   }
//   exit;
// }

// void spinSlow() {
//   enableMotor(BOTH_MOTORS);
//   setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
//   setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD);
//   setMotorSpeed(LEFT_MOTOR, 10);
//   setMotorSpeed(RIGHT_MOTOR, 10);
// }
