#include <IRremote.h>

const int RECV_PIN = 6;
IRrecv IR(RECV_PIN);
decode_results results;
unsigned long decode;

void setup(){
  Serial.begin(9600);
  IR.enableIRIn();
}

void loop(){
  if(IR.decode()) {
    decode = IR.decodedIRData.decodedRawData;
    Serial.println(decode, HEX); 
    //delay(1500);
    IR.resume(); 
  }
}
