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
