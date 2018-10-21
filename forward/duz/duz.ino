#include <MedianFilter.h>
#include <Servo.h> 
#include <SoftPWM.h>

#include <Wire.h>
#define SLAVE_ADDRESS 0x04
Servo myservo;
int number=0;
int Cx=200;
int state = 0;
int dist=0;
int cm=50;
int i;
int top=0;
int pos=0;
int x = 200 ; // coordinat  
int ref = 200; // middle pixel
int error = 0; // difference
int k = 1; // cons
int kerror= 0; // final error
int PWMA= 255; // final error
int PWMB= 255; // final error
int counter=0;
int cny1=0;
int cny2=0;
int ballpicked=0;
const int trigPin = 3;
const int echoPin = 2;
 long duration, inches;
int inputPin = 12;
int ir = 0;
int sen1;
int sen2;

int irSenRead =40;
int isObstacle = HIGH;


void setup() {
  // initialize serial communication:
  Serial.begin(115200);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  pinMode(inputPin, INPUT);
  myservo.attach(4);
  SoftPWMBegin();
  SoftPWMSet(5, 0);
  SoftPWMSetFadeTime(5, 10, 10); //enable a
  SoftPWMSet(11, 0);
  SoftPWMSetFadeTime(11, 10, 10); // enable b
  SoftPWMSet(10, 0);
  SoftPWMSetFadeTime(10, 10, 10); //enable screw

  
  SoftPWMSet(8, 0);
  SoftPWMSetFadeTime(8, 10, 10);   //motor a
  SoftPWMSet(9, 0);
  SoftPWMSetFadeTime(9, 10, 10);   
  
  SoftPWMSet(12, 0);
  SoftPWMSetFadeTime(12, 10, 10);   //motor screw
  SoftPWMSet(13, 0);
  SoftPWMSetFadeTime(13, 10, 10);   
  
  SoftPWMSet(6, 0);
  SoftPWMSetFadeTime(6, 10, 10);   //motor b
  SoftPWMSet(7, 0);
  SoftPWMSetFadeTime(7, 10, 10);




  pinMode(irSenRead ,INPUT);
   Serial.begin(115200);



}

void loop() {


error = ref - Cx ; 
kerror = k * error ; 
PWMA = 200-kerror;
PWMB= 200+kerror;
  
   isObstacle = digitalRead(irSenRead); // // Read IR sensor output
   Serial.println(digitalRead(irSenRead)); // // print the output
 
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/5);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/5);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   


delay(20);
     Serial.print("TOP 15'DEN UZAKTA");
     Serial.print('\n');
     delay(80);

}

void receiveData(int byteCount) {
  int i = 0;
  while (Wire.available()) {
    number = Wire.read();
    Cx=number*2;
    
  }
  //Serial.println("Cx");
  //Serial.print(Cx);
  //Serial.print('\n');
}  // end while

// callback for sending data
void sendData() {
if (Serial.available()){
    ballpicked = Serial.read() ; 
    }
    Wire.write(ballpicked);
    Wire.write(number);
}




