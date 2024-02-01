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

void goldVotive(){
    Serial.println("Lighting Gold Votive");
    IRsent.protocol = NEC;
    IRsent.address = 0xEE;
    IRsent.command = 160;
    IRsent.isRepeat = false;
    sendIR.write(&IRsent);
    delay(100);
}
