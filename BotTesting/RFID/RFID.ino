#include<SoftwareSerial.h>

SoftwareSerial ssrfid(7,8);
//const val = 0;

void setup()
{
  Serial.begin(9600);
  ssrfid.begin(9600);
  ssrfid.listen();

  Serial.write("Initialized");

  
}

void loop(){
  
  if(ssrfid.available() > 0){
    for(int i = 0; i <= 14;i++){
      char val = ssrfid.read();
      Serial.write(val);
    }
    Serial.println();
 }
 

}

void rfid(SoftwareSerial ssrfid){
    if(ssrfid.available() > 0){
    for(int i = 0; i <= 14;i++){
      char val = ssrfid.read();
      Serial.write(val);
    }
    Serial.println();
 }
}
