/*
  Transmitter.ino - Arduino Sketch for IR Transmissions
    uses objects from:
    RobotTemplate.ino

    Uses the second IRLED (IR Transmitter), to send messages and 
    the IR Receiver to receive messages
     IR Transmitter     P2.5
     IR Reciever        P5.1
  
  This file allows the robot to transmit: 
    a random IR message 
    a predetermined IR code
    a IR code that is received then sent back to its orignal sender

  Created by: Jennings Brooklyn, Rohan Malipeddi, Luis Hernandez Aguirre
  Date: Feb 11, 2024
*/

/*
This functions allows us to light up the Catrina Skull Candle
it first receives an IR message then repeats the message back to the original sender
*/
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

/*
This functions allows us to light up the Gold Voltive Candle
it transmits a predetermined IR message 
*/
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

/*
This functions allows us to light up the Black Voltive Candle
it transmits a IR signal
*/
void blackVotive(){
    Serial.println("Lighting Black Candle");
    delay(100);

    digitalWrite(IR_LED_SIMPLE,HIGH);
    delay(100);

    digitalWrite(IR_LED_SIMPLE,LOW);
}
