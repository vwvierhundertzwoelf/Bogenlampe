#include <AH_28BYJ48.h>

#define current_input 0

const int stepsPerRevolution = 64*64;  // number of steps per revolution * gear factor
int target = 20;
long striketime = 0;
int on = 1;
int strike = 0;

AH_28BYJ48 myStepper(stepsPerRevolution, 8,9,10,11);

void setup() {
  // put your setup code here, to run once:
  analogReference(INTERNAL);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(map(analogRead(current_input), 0, 1024, 0, 200));
  
  if(map(analogRead(current_input), 0, 1024, 0, 200) < 19 && on == 1){
    while(map(analogRead(current_input), 0, 1024, 0, 200) < 21){
      myStepper.setSpeedHz(100);
      myStepper.step(10);
    }
  }
  
  if(map(analogRead(current_input), 0, 1024, 0, 200) > 15 && strike == 0) strike = 1, striketime = millis();
  
  if(map(analogRead(current_input), 0, 1024, 0, 200) < 5 && strike == 1 && (millis()-striketime) > 10000){
    myStepper.setSpeedHz(100);
    myStepper.step(-10000);
    strike = 0;
    on = 0;
  } 
}
