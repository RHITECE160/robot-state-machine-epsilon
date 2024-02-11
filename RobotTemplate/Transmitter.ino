/*
  Transmitter.ino - Arduino Sketch for IR Transmissions

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
    if(receiveIR.decodeIR(&IRreceived)){
    IRsent.protocol = NEC;
    IRsent.address = 0xCE;
    IRsent.command = IRreceived.command;
    IRsent.isRepeat = false;
    }
    sendIR.write(&IRsent);
    delay(100);
}

/*
This functions allows us to light up the Gold Voltibe Candle
it transmits a predetermined IR message 
*/
void goldVotive(){
    Serial.println("Lighting Gold Votive");
    IRsent.protocol = NEC;
    IRsent.address = 0xEE;
    IRsent.command = 160;
    IRsent.isRepeat = false;
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
