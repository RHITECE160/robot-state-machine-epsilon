/*
  RemoteControl.ino - Arduino Sketch for Remote Control of the RLSK robot
  
  Description:
  This sketch provides functions for controlling an RLSK robot using a
  playstation controller for input.  

  Button map:
  Left joystick to move forward, back, right and left
  Press both joysticks down to engage autonomous mode

  R2 to spin (Counterclockwise)
  L2 to spinOtherWay (clockwise)
  R1 to open claw
  L1 to close claw

  PAD UP - light gold votive
  PAD DOWN - light catrina
  PAD LEFT - light black votive

  Created by: Rohan Malipeddi, Luis Hernandez Aguirre, Brooklyn Jennings
  Date: Feb 11, 2024
*/

/* RemoteControl() function
This function uses a playstation controller and the PLSK libraray with
an RLSK robot using to implement remote controller.
*/
void RemoteControl(PS2X Controller, Servo myServo) {
    //checks if the joystick is moved
    if (Controller.Analog(PSS_LY) >= 255*0.55 || Controller.Analog(PSS_LY) <= 255*0.45) {
      //assigning a value for y position of the joystick
      int yVal = Controller.Analog(PSS_LY);
      //the joystick becomes less as I move it forward, so condition is opposite
      if(yVal < 128) {  
        //mapped to specific speeds
        int speedSetting = map((255-Controller.Analog(PSS_LY)), 255*0.55, 255, 0, 20);
        forward(speedSetting);
      }
      else {
        //mapped to specific speeds
        int speedSetting = map((Controller.Analog(PSS_LY)-128), 0, 255*0.45, 0, 20);
        back(speedSetting);
      }
    } 
    //joystick moved?
    else if(Controller.Analog(PSS_LX) >= 255*0.55 || Controller.Analog(PSS_LX) <= 255*0.45) {
      //assigning a value for x position of the joystick
      int xVal = Controller.Analog(PSS_LX);
      //horizontal motoin moves like normal
      if(xVal > 128) {
        //mapped to specific speeds
        int speedSetting = map(255-Controller.Analog(PSS_LX), 255*0.55, 255, 0, 10);
        TurnRight(speedSetting);
      }
      else {
        //mapped to specific speeds
        int speedSetting = map((Controller.Analog(PSS_LX)-128), 0, 255*0.45, 0, 10);
        TurnLeft(speedSetting);
      }
    }

    //spin mapping
    else if(Controller.Button(PSB_R2)) {
      Serial.println("R2 button pushed ");
      spin();
    }
    //claw open map
    else if(Controller.Button(PSB_R1)) {
      Serial.println("R1 button pressed");
      Openclaw(myServo);
    } 
    //claw close map
    else if(Controller.Button(PSB_L1)) {
      Serial.println("L1 button pressed");
      Closeclaw(myServo);
    }
    //spin other way map
    else if(Controller.Button(PSB_L2)) {
      Serial.println("L2 button pushed ");
      spinOtherWay();
    }
    // pad left to light up the black candle
    else if(Controller.Button(PSB_PAD_LEFT)){
      Serial.println("Left Pad button pushed ");
      blackVotive();
    }
    //pad up for lighting gold votive
    else if(Controller.Button(PSB_PAD_UP)){
      Serial.println("Up Pad button pushed ");
      goldVotive();
    }
    //pad down for lighting catrina
    else if(Controller.Button(PSB_PAD_DOWN)){
      Serial.println("Down Pad button pushed ");
      catrinaSkull();
    }
    //default stop if nothing pressed
    else {
      stop();
    }
}