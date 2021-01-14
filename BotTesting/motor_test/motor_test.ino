
#define STEPPIN 12
#define DIRPIN 11
#define ENABLE 10

int PISignal = 0;

void setup() {
 Serial.begin(9600);
 pinMode(DIRPIN, OUTPUT);
 pinMode(STEPPIN, OUTPUT);
 pinMode(ENABLE,OUTPUT);

}

void loop() {
/*forward(1000);
delay(1000);
backwards(1000);*/
Serial.println("Connected");
//PIinput();
forward(1000);
delay(100);
backwards(1000);

}


void forward(int steps){
  digitalWrite(ENABLE,LOW);
  digitalWrite(DIRPIN, LOW);

  for(int i = 0; i < steps;i++){
    digitalWrite(STEPPIN, !digitalRead(STEPPIN));
  
      delay(1);
    
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

void PIinput(){
  if(Serial.available() > 0){
      PISignal = Serial.read();

      if(PISignal = 'w'){
        forward(1000);
      }
  }
}
