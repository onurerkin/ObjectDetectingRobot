//#include <MedianFilter.h>
#include <Servo.h> 
#include <SoftPWM.h>
// Ikinci IR 41.pinde!!!!!!!
#include <Wire.h>
#define SLAVE_ADDRESS 0x7F
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
int iter=0;
int irSenRead =40;
int isObstacle = HIGH;
int uzak = HIGH;
int reference = 150;
int pota = HIGH;

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
  
  isObstacle = digitalRead(irSenRead); // // Read IR sensor output
   Serial.println(digitalRead(irSenRead)); // // print the output


uzak = digitalRead(41); // // Read IR sensor output
   Serial.println(digitalRead(41)); // // print the output

pota = digitalRead(39); // // Read IR sensor output
   Serial.println(digitalRead(39)); // // print the output
   
int sen1 = analogRead(A0);// Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor
int sen2 = analogRead(A1);// Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor

if (sen1 > reference || sen2 > reference){
ballpicked = 20;
Serial.println("Picked");
}
else{
ballpicked = 5;
Serial.println("Not Picked");
}


if(sen1<reference){
  cny1=0;
}
else{
  cny1=1;
}

if(sen2<reference){
  cny2=0;
}
else{
  cny2=1;
}



/*
     //Serial.print("cm:");
     //Serial.print(cm);
     Serial.print('\n');
     Serial.print("number:");
     Serial.print(number);
     Serial.print('\n');
     Serial.print("cny1:");
     Serial.print(cny1);
     Serial.print('\n');
     Serial.print("cny2:");
     Serial.print(cny2);
     Serial.print('\n');
     Serial.print("Cx:");
     Serial.print(Cx);
     Serial.print('\n');
    // Serial.print("Ball Picked:");
    // Serial.print(ballpicked);
    // Serial.print('\n');
     Serial.print("sen1:");
     Serial.print(sen1);
     Serial.print('\n');
     Serial.print("sen2:");
     Serial.print(sen2);
     Serial.print('\n');

*/
 

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  dist = int(microsecondsToCentimeters(duration));

  //aq.in(dist);
  //cm = aq.out();
  cm=dist;

ir = digitalRead(inputPin);

 
error = ref - Cx ; 
kerror = k * error ; 
PWMA = 200-kerror;
PWMB= 200+kerror;


iter=0;

 if ( number == 0 && cny1==0 && cny2==0 ) {                  // BURDA ETRAFINDA DONUYOR

digitalWrite(48, LOW);
  digitalWrite(49, LOW);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
  
while(iter<10){

  Serial.print("number:");
     Serial.print(number);
     Serial.print('\n');

  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 40);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 40);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);  

delay(200);



  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 20);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 20);//digitalWrite(8, LOW);  

delay(10);

iter=iter+1;

if(number!=0){
  break;
  } }

  while(iter>9 && iter<30){
Serial.print("number:");
     Serial.print(number);
     Serial.print('\n');
    
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 40);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 40);//digitalWrite(8, LOW);  

delay(200);



  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 20);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 20);//digitalWrite(8, LOW);  

delay(10);

iter=iter+1;

if(number!=0){
  break;
  }  
  }

while(iter>29){

Serial.print("number:");
     Serial.print(number);
     Serial.print('\n');

//delay(40);      //arada koordinat gelmezse diye



  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 20);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 20);//digitalWrite(8, LOW);  

delay(200);



  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 20);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 20);//digitalWrite(8, LOW);  

delay(30);


if(number!=0){
  break;
  }  
  }

}

 else if ( isObstacle==1 && number!=0 && cny1==0 && cny2==0 && uzak==1  ) {  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/2);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/2);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   


    delay(400);
  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);
  SoftPWMSet(9, PWMA-75);//digitalWrite(8, LOW); 
  
  SoftPWMSet(6, PWMB-75);//digitalWrite(7, HIGH); 
  SoftPWMSet(7, 0);//digitalWrite(8, LOW); 

delay(5);
     Serial.print("TOP 15'DEN UZAKTA");
     Serial.print('\n');

digitalWrite(48, HIGH);
  digitalWrite(49, LOW);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
     
 }

 else if ( isObstacle==1 && number!=0 && cny1==0 && cny2==0 && uzak==0 ) {  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/4);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/4);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   


    delay(400);
  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);
  SoftPWMSet(9, PWMA-75);//digitalWrite(8, LOW); 
  
  SoftPWMSet(6, PWMB-75);//digitalWrite(7, HIGH); 
  SoftPWMSet(7, 0);//digitalWrite(8, LOW); 

delay(10);
     Serial.print("TOP 15'DEN UZAKTA");
     Serial.print('\n');

     digitalWrite(48, HIGH);
  digitalWrite(49, LOW);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);


 }
else if ( isObstacle==0 && cny1==0 && cny2==0 ) { 

/*
sen1 = analogRead(A0);// Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor
sen2 = analogRead(A1);// Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor


if(sen1<150){
  cny1=0;
}
else{
  cny1=1;
}

if(sen2<150){
  cny2=0;
}
else{
  cny2=1;
}
*/
   
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW); 

  delay(1000);
while(counter<1 && cny1==0 && cny2==0 && isObstacle==0 ){


sen1 = analogRead(A0);// Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor
sen2 = analogRead(A1);// Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor


if(sen1<reference){
  cny1=0;
}
else{
  cny1=1;
}

if(sen2<reference){
  cny2=0;
}
else{
  cny2=1;
}
  

   for(pos = 0; pos <= 180; pos +=20) // goes from 15 degrees to 180 degrees 
   {                                  // in steps of 6 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(60);                       // waits 15ms for the servo to reach the position 
  } 

  delay(1000);
 for(pos = 180; pos >= 0 ; pos-=20)     // goes from 180 degrees to 15 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
   delay(60);                       // waits 15ms for the servo to reach the position 
  } 
  counter=counter+1;
 /*   pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
 // delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
*/
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.


  // convert the time into a distance


     Serial.print("Top 3DEN AZ, ALIYORUM");
     Serial.print('\n');

      SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 100);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 100);//digitalWrite(8, LOW);

    delay(1000);
  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 100);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 100);//digitalWrite(8, LOW);
delay(1000);
}
while(counter==3){

sen1 = analogRead(A0);// Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor
sen2 = analogRead(A1);// Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor


if(sen1<reference){
  cny1=0;
}
else{
  cny1=1;
}

if(sen2<reference){
  cny2=0;
}
else{
  cny2=1;
}
  
  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 100);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 100);//digitalWrite(8, LOW);
 
  /*pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
*/
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.


  // convert the time into a distance


    
     Serial.print("10 KEREDE ALAMADIM, BREAK");
     Serial.print('\n');

     digitalWrite(48, LOW);
  digitalWrite(49, LOW);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
  delay(1000);
  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 100);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 100);//digitalWrite(8, LOW);
delay(1000);


  

counter=0;
  break;
  
}
counter=0;
}



 // delay(30);

  
while(cny2==1){

sen1 = analogRead(A0);// Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor
sen2 = analogRead(A1);// Arduino’nun A1 ayağına bağlanan kablodaki gerilim ölçülüyor


if(sen1<reference){
  cny1=0;
}
else{
  cny1=1;
}

if(sen2<reference){
  cny2=0;
}
else{
  cny2=1;
}



     Serial.print("YUVAYA TOPU SOKMAYA CALISIYORUM");
     Serial.print('\n');
  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   
  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW); 
  
  SoftPWMSet(10, 255);//digitalWrite(6, LOW);   
  SoftPWMSet(12, 150);//digitalWrite(7, HIGH);   
  SoftPWMSet(13, 0);//digitalWrite(8, LOW); 

  delay(100);
  SoftPWMSet(10, 0);//digitalWrite(6, LOW);   
  SoftPWMSet(12, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(13, 0);//digitalWrite(8, LOW); 

  if (cny2==0){
    break;
  }
}



if ( number==0 && cny1==1) {                  // BURDA ETRAFINDA DONUYOR


  digitalWrite(48, LOW);
  digitalWrite(49, LOW);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 70);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 70);//digitalWrite(8, LOW); 

  delay(500);

  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 50);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 50);//digitalWrite(8, LOW); 

  delay(20);

     Serial.print("TOPU ALDIM, POTAYI ARIYORUM");
     Serial.print('\n');
     
     digitalWrite(48, LOW);
  digitalWrite(49, LOW);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
 }


else if (  number!=0 && cny1==1 && uzak==1) {  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/2);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/2);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

delay(600);


  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/4);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/4);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

  delay(20);
  
     Serial.print("Topu aldım, potayı goruyorum, pota>15cm");
     Serial.print('\n');  
     digitalWrite(48, LOW);
  digitalWrite(49, HIGH);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
 }


else if ( number!=0 && cny1==1 && uzak==0 && pota==1 ) {  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/6);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/6);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

delay(300);


  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/4);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/4);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

  delay(20);
  
     Serial.print("Topu aldım, potayı goruyorum, pota>15cm");
     Serial.print('\n');  
     digitalWrite(48, LOW);
  digitalWrite(49, HIGH);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
 }






isObstacle=0;
isObstacle = digitalRead(irSenRead); // // Read IR sensor output


if ( pota==0 && cny1==1 && number!=0) { 
    SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);  

delay(50);

  
     myservo.write(60);
     Serial.print("Topu aldım, potayı goruyorum, pota<3cm UCLUK ATIYORUM");
     Serial.print('\n');  
     digitalWrite(48, LOW);
  digitalWrite(49, LOW);
  digitalWrite(50, HIGH);
  digitalWrite(51, LOW);




  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW); 

  delay(1000);
  

  SoftPWMSet(10, 255);//digitalWrite(6, LOW);   
  SoftPWMSet(12, 225);//digitalWrite(7, HIGH);   
  SoftPWMSet(13, 0);//digitalWrite(8, LOW); 

  delay(8000); 

  SoftPWMSet(10, 0);//digitalWrite(6, LOW);   
  SoftPWMSet(12, 150);//digitalWrite(7, HIGH);   
  SoftPWMSet(13, 0);//digitalWrite(8, LOW); 

  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 50);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 50);//digitalWrite(8, LOW); 
  
  delay(1000);



  
}

 number=0;

delay(100);

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

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

