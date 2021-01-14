#include<SoftwareSerial.h>

#define STEPPIN 12
#define DIRPIN 11
#define ENABLE 10


void setup() {
  
 Serial.begin(9600);
 
 pinMode(DIRPIN, OUTPUT);
 pinMode(STEPPIN, OUTPUT);
 pinMode(ENABLE,OUTPUT);

}



void loop() {
 
}

void GetPosition(int X_POS, int Y_POS){

  forward(X_POS*1000);
  
  
}

void forward(int steps){
  digitalWrite(ENABLE,LOW);
  digitalWrite(DIRPIN, LOW);

  for(int i = 0; i < steps;i++){
    digitalWrite(STEPPIN, !digitalRead(STEPPIN));
  {
      delay(1);
    }
  }
  digitalWrite(ENABLE, HIGH);
}

void backwards(int steps){
  digitalWrite(ENABLE,LOW);
  digitalWrite(DIRPIN,HIGH);

  for(int i = 0;i < steps;i++){
    digitalWrite(STEPPIN, !digitalRead(STEPPIN));
 
      delay(1);
    }
  
  digitalWrite(ENABLE,HIGH);
}
