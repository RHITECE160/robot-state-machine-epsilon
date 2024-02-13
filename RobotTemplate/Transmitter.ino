/*
Functions to light the candles that need specific transmissions
  uses objects from:
  RobotTemplate.ino

    Uses the second IRLED (IR Transmitter), to send messages and 
    the IR Receiver to receive messages
     IR Transmitter     P2.5
     IR Reciever        P5.1
     
  written for the MSP432401 board
  Author: Jennings Brooklyn, Rohan Malipeddi, Luis Hernandez
  Last revised: 2/5/2024
*/

//function to light a catrina skull when called
void catrinaSkull(){
    Serial.println("Lighting Catrina");
    //Saves the recieved message into the outgoing message variables
    if(receiveIR.decodeIR(&IRreceived)){
    IRsent.protocol = NEC;
    IRsent.address = 0xCE;
    IRsent.command = IRreceived.command;
    IRsent.isRepeat = false;
    }
    //writes outgoing message
    sendIR.write(&IRsent);
    delay(100);
}

//function to light votive candle when called
void goldVotive(){
    Serial.println("Lighting Gold Votive");
    //sets the outgoing command to the preset votive candle command
    IRsent.protocol = NEC;
    IRsent.address = 0xEE;
    IRsent.command = 160;
    IRsent.isRepeat = false;
    //writes outgoing command
    sendIR.write(&IRsent);
    delay(100);
}
