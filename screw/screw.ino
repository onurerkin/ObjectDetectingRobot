#include <SoftPWM.h>


void setup() {
    Serial.begin(115200);
  SoftPWMBegin();

  // put your setup code here, to run once:
SoftPWMSet(10, 0);
  SoftPWMSetFadeTime(10, 10, 10); //enable screw
  SoftPWMSet(12, 0);
  SoftPWMSetFadeTime(12, 10, 10);   //motor screw
  SoftPWMSet(13, 0);
  SoftPWMSetFadeTime(13, 10, 10);   
}

void loop() {
  // put your main code here, to run repeatedly:
  SoftPWMSet(10, 255);//digitalWrite(6, LOW);   
  SoftPWMSet(12, 205);//digitalWrite(7, HIGH);   
  SoftPWMSet(13, 0);//digitalWrite(8, LOW); 
}
