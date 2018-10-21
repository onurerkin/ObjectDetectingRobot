//#include <MedianFilter.h>
#include <Servo.h> 
#include <SoftPWM.h>
#define sensor A2 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)
Servo myservo;
int Cx;
int ballpicked;
int state = 0;
int dist=0;
int cm=50;
int i;
int top=0;
int pos=0;
int x = 200 ; // coordinat  
int ref = 200; // middle pixel
float error = 0; // difference
float k = 1; // cons
float kerror= 0; // final error
int PWMA= 0; // final error
int PWMB= 0; // final error
int counter=0;
int cny1=0;
int cny2=0;
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
int yakin2 = HIGH;
int reference = 500;
int pota1 = HIGH;
int pota2 = HIGH;
int pin0 = 22;
int pin1 = 23;
int pin2 = 24;
int pin3 = 25;
int pin4 = 26;
int pin5 = 27;
int pin6 = 28;
int pin7 = 29;
int pin8 = 30;
int pincny = 34;
int pin_blue_ball = 36;
float volts;
int irdist;




void setup() {



   
  // initialize serial communication:
  Serial.begin(115200);
  pinMode(inputPin, INPUT);
    pinMode(pin0, INPUT);
    pinMode(pin1, INPUT);
    pinMode(pin2, INPUT);
    pinMode(pin3, INPUT);
    pinMode(pin4, INPUT);
    pinMode(pin5, INPUT);
    pinMode(pin6, INPUT);
    pinMode(pin7, INPUT);
    pinMode(pin8, INPUT);
    pinMode (pincny,OUTPUT);
    pinMode (pin_blue_ball,OUTPUT);


 pinMode(46, OUTPUT); //Segmentde "A" kısmı
  pinMode(47, OUTPUT); //Segmentde "B" kısmı
  pinMode(48, OUTPUT); //Segmentde "C" kısmı
  pinMode(49, OUTPUT); //Segmentde "D" kısmı
  pinMode(50, OUTPUT); //Segmentde "E" kısmı
  pinMode(51, OUTPUT); //Segmentde "F" kısmı
  pinMode(52, OUTPUT); //Segmentde "G" kısmı
  pinMode(53, OUTPUT); //Segmentde "DP" kısmı (Nokta kısmı)

    
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
  digitalWrite(pin_blue_ball, HIGH);   
}





void loop() {

   
 Serial.print("cny1:");
 Serial.print(cny1);
 Serial.print('\n'); 
  Serial.print("cny2:");
 Serial.print(cny2);
 Serial.print('\n'); 

  
    Cx = 0;
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;



   


 Serial.print("pota1:");
 Serial.print(pota1);
 Serial.print('\n'); 
 Serial.print("pota2:");
 Serial.print(pota2);
 Serial.print('\n'); 
 
  
  digitalWrite(pincny, LOW); 
irdist=30; 
volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
irdist = 13*pow(volts, -1); // worked out from datasheet graph

 Serial.print("irdist:");
 Serial.print(irdist);
 Serial.print('\n'); 



   
isObstacle = digitalRead(irSenRead); // // Read IR sensor output
   //Serial.println(digitalRead(irSenRead)); 
if (irdist<10){
  uzak=0;
}
else if (irdist>9){
  uzak=1;
  }

pota1 = digitalRead(38); // // Read IR sensor output
   //Serial.println(digitalRead(39))8 

pota2 = digitalRead(41); // // Read IR sensor output

yakin2 = digitalRead(44);

int sen1 = analogRead(A0);
int sen2 = analogRead(A1);

if (sen1 > reference || sen2 > reference){
  ballpicked = 1;
  digitalWrite(pincny,HIGH); 
  //Serial.println("Picked");
  }
  else{
  ballpicked = 0;
  digitalWrite(pincny,LOW); 
  //Serial.println("Not Picked");
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
     Serial.print("Cx:");
     Serial.print(Cx);
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
     Serial.print("sen1:");


*/
 

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:


  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.


  // convert the time into a distance


  //aq.in(dist);
  //cm = aq.out();


ir = digitalRead(inputPin);

 
error = ref - Cx ; 
kerror = k * error ; 
PWMA = int(200-kerror);
PWMB= int(200+kerror);


iter=0;

if ( Cx == 0 && cny1==0 && cny2==0 ) {                  // BURDA ETRAFINDA DONUYOR


 digitalWrite(46, 1);
 digitalWrite(47, 1);
 digitalWrite(48, 1);
 digitalWrite(49, 1);
 digitalWrite(50, 1);
 digitalWrite(51, 1);
 digitalWrite(52, 0);
 digitalWrite(53, 0);

      digitalWrite(48, LOW);
      digitalWrite(49, LOW);
      digitalWrite(50, LOW);
      digitalWrite(51, LOW);
      
    while(iter<1){



     
    Cx = 0;
 
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;
   
     iter=iter+1;
    
    if(Cx!=0){
      break;
      } }

      delay(100);
    
    
      SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
      SoftPWMSet(11, 255);//digitalWrite(6, LOW);   
      
      SoftPWMSet(8, 25);//digitalWrite(7, HIGH);   
      SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
      
      SoftPWMSet(6, 25);//digitalWrite(7, HIGH);   
      SoftPWMSet(7, 0);//digitalWrite(8, LOW);  
    
    /*delay(400);
    
    
      SoftPWMSet(5, 0);//digitalWrite(5, HIGH);   
      SoftPWMSet(11, 0);//digitalWrite(6, LOW);   
    

      
      SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
      SoftPWMSet(9, 20);//digitalWrite(8, LOW);   
      
      SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
      SoftPWMSet(7, 20);//digitalWrite(8, LOW);  
    
    delay(10);*/
    
    

    


   
    while(iter>0){

    
    Cx = 0;
 
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;


   
         Serial.print("Cx:");
         Serial.print(Cx);
         Serial.print('\n');
Serial.print("irdist:");
 Serial.print(irdist);
 Serial.print('\n'); 
             
    
      SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
      SoftPWMSet(11, 255);//digitalWrite(6, LOW);   
      
      SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
      SoftPWMSet(9, 25);//digitalWrite(8, LOW);   
      
      SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
      SoftPWMSet(7, 25);//digitalWrite(8, LOW);  
    
    /*delay(400);  
    
      SoftPWMSet(5, 0);//digitalWrite(5, HIGH);   
      SoftPWMSet(11, 0);//digitalWrite(6, LOW);   
      
      SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
      SoftPWMSet(9, 20);//digitalWrite(8, LOW);   
      
      SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
      SoftPWMSet(7, 20);//digitalWrite(8, LOW);  
    
    delay(30);*/
    
    
    if(Cx!=0){
      break;
      }  
      }

}





 else if (  Cx!=0 && cny1==0 && cny2==0 && uzak==1 &&  isObstacle==1 ) {  


 digitalWrite(46, 0);
 digitalWrite(47, 1);
 digitalWrite(48, 1);
 digitalWrite(49, 0);
 digitalWrite(50, 0);
 digitalWrite(51, 0);
 digitalWrite(52, 0);
 digitalWrite(53, 0);

  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/3.1);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/3.1);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   


    /*delay(500);
  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);

  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);
  SoftPWMSet(9, PWMA-75);//digitalWrite(8, LOW); 
  
  SoftPWMSet(6, PWMB-75);//digitalWrite(7, HIGH); 
  SoftPWMSet(7, 0);//digitalWrite(8, LOW); 

  delay(5);*/
  
     Serial.print("TOP 15'DEN UZAKTA");
     Serial.print('\n');

  digitalWrite(48, HIGH);
  digitalWrite(49, LOW);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
     
 }
  


   
 else if ( isObstacle==1 && yakin2==1 && Cx!=0 && cny1==0 && cny2==0 && uzak==0 ) {  


 digitalWrite(46, 0);
 digitalWrite(47, 1);
 digitalWrite(48, 1);
 digitalWrite(49, 0);
 digitalWrite(50, 0);
 digitalWrite(51, 0);
 digitalWrite(52, 0);
 digitalWrite(53, 0);
  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/6);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/6);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   


    /*delay(400);
  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);
  SoftPWMSet(9, PWMA-75);//digitalWrite(8, LOW); 
  
  SoftPWMSet(6, PWMB-75);//digitalWrite(7, HIGH); 
  SoftPWMSet(7, 0);//digitalWrite(8, LOW); 

    delay(10);*/

    
     Serial.print("TOP 15'DEN UZAKTA");
     Serial.print('\n');

     digitalWrite(48, HIGH);
     digitalWrite(49, LOW);
     digitalWrite(50, LOW);
     digitalWrite(51, LOW);


 }
    Cx = 0;
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;

   

   
 Serial.print("CxT:");
 Serial.print(Cx);
 Serial.print('\n'); 

 
if (( isObstacle==0 || yakin2==0) && cny1==0 && cny2==0 ) { 
  
 digitalWrite(46, 1);
 digitalWrite(47, 1);
 digitalWrite(48, 0);
 digitalWrite(49, 1);
 digitalWrite(50, 1);
 digitalWrite(51, 0);
 digitalWrite(52, 1);
 digitalWrite(53, 0);
 
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

  delay(100);
while(counter<1 && cny1==0 && cny2==0 && (isObstacle==0 || yakin2==0)){

Cx = 0;
  
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;
   

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


  
  SoftPWMSet(8, 120);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 120);//digitalWrite(8, LOW);

    delay(1500);
  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 100);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 100);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);
delay(2500);
}
/*while(counter==3){

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
        
}*/
counter=0;
}

while(cny2==1){

 digitalWrite(46, 1);
 digitalWrite(47, 1);
 digitalWrite(48, 0);
 digitalWrite(49, 1);
 digitalWrite(50, 1);
 digitalWrite(51, 0);
 digitalWrite(52, 1);
 digitalWrite(53, 0);

  Cx = 0;
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;
   
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
         Serial.print(sen1);
     Serial.print('\n');
     Serial.print("sen2:");
     Serial.print(sen2);
     Serial.print('\n');
    
    
         Serial.print("YUVAYA TOPU SOKMAYA CALISIYORUM");
         Serial.print('\n');


 Serial.print("cny1:");
 Serial.print(cny1);
 Serial.print('\n'); 
  Serial.print("cny2:");
 Serial.print(cny2);
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

    Cx = 0;
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;

   

   
 Serial.print("cny1:");
 Serial.print(cny1);
 Serial.print('\n'); 
  Serial.print("cny2:");
 Serial.print(cny2);
 Serial.print('\n'); 


if ( Cx==0 && cny1==1) {                  //  YESIL ICIN BURDA ETRAFINDA DONUYOR


 digitalWrite(46, 1);
 digitalWrite(47, 1);
 digitalWrite(48, 1);
 digitalWrite(49, 1);
 digitalWrite(50, 0);
 digitalWrite(51, 0);
 digitalWrite(52, 1);
 digitalWrite(53, 0);
  

  digitalWrite(48, LOW);
  digitalWrite(49, LOW);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 30);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 30);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW); 

  /*delay(500);

  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 50);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 50);//digitalWrite(8, LOW); 

  delay(20);*/

     Serial.print("TOPU ALDIM, POTAYI ARIYORUM");
     Serial.print('\n');
     
     digitalWrite(48, LOW);
     digitalWrite(49, LOW);
     digitalWrite(50, LOW);
     digitalWrite(51, LOW);
 }


   
else if (  Cx!=0 && cny1==1 && uzak==1) {  


 digitalWrite(46, 0);
 digitalWrite(47, 1);
 digitalWrite(48, 1);
 digitalWrite(49, 0);
 digitalWrite(50, 0);
 digitalWrite(51, 1);
 digitalWrite(52, 1);
 digitalWrite(53, 0);

  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/2.8);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/2.8);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

/*delay(700);


  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

  delay(20);*/
  
   Serial.print("Topu aldım, potayı goruyorum, pota>15cm");
   Serial.print('\n');  
   digitalWrite(48, LOW);
  digitalWrite(49, HIGH);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
 }

    Cx = 0;
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;

   

   
 Serial.print("CxC:");
 Serial.print(Cx);
 Serial.print('\n'); 

 
if ( Cx!=0 && cny1==1 && uzak==0 && pota1==1 && pota2==1 ) { 
  
   digitalWrite(46, 0);
 digitalWrite(47, 1);
 digitalWrite(48, 1);
 digitalWrite(49, 0);
 digitalWrite(50, 0);
 digitalWrite(51, 1);
 digitalWrite(52, 1);
 digitalWrite(53, 0); 
 
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/12);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/12);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

delay(300);


  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);
  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/4);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/4);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

  delay(30);
  
     Serial.print("Pota yakında");
     Serial.print('\n');  
     digitalWrite(48, LOW);
  digitalWrite(49, HIGH);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
 }

    Cx = 0;
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;

   

   
 Serial.print("CxD:");
 Serial.print(Cx);
 Serial.print('\n'); 


if ( cny1==1 && uzak==0 && pota1==0 && pota2==1 ) {  

 digitalWrite(46, 1);
 digitalWrite(47, 0);
 digitalWrite(48, 1);
 digitalWrite(49, 1);
 digitalWrite(50, 0);
 digitalWrite(51, 1);
 digitalWrite(52, 1);
 digitalWrite(53, 0);

  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 30);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 30);//digitalWrite(8, LOW);   

delay(100);


  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);
  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/4);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/4);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

  delay(30);
  
     Serial.print("Pota solda");
     Serial.print('\n');  
     digitalWrite(48, LOW);
  digitalWrite(49, HIGH);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
 }




else if ( cny1==1 && uzak==0 && pota2==0 && pota1==1 ) {  

 digitalWrite(46, 1);
 digitalWrite(47, 0);
 digitalWrite(48, 1);
 digitalWrite(49, 1);
 digitalWrite(50, 0);
 digitalWrite(51, 1);
 digitalWrite(52, 1);
 digitalWrite(53, 0);

  
  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);


  
  SoftPWMSet(8, 30);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 30);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

delay(100);


  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);
  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, PWMA/4);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, PWMB/4);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 0);//digitalWrite(8, LOW);   

  delay(30);
  
     Serial.print("pota sagda");
     Serial.print('\n');  
     digitalWrite(48, LOW);
  digitalWrite(49, HIGH);
  digitalWrite(50, LOW);
  digitalWrite(51, LOW);
 }

yakin2=0;
yakin2 = digitalRead(44);
isObstacle=0;
isObstacle = digitalRead(irSenRead); // // Read IR sensor output


    Cx = 0;
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;

   

   
 Serial.print("Cx:");
 Serial.print(Cx);
 Serial.print('\n'); 



if ( pota1==0 && pota2==0 && cny1==1) { 

 digitalWrite(46, 1);
 digitalWrite(47, 0);
 digitalWrite(48, 1);
 digitalWrite(49, 1);
 digitalWrite(50, 1);
 digitalWrite(51, 1);
 digitalWrite(52, 1);
 digitalWrite(53, 0);


  
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
  SoftPWMSet(12, 215);//digitalWrite(7, HIGH);   
  SoftPWMSet(13, 0);//digitalWrite(8, LOW); 

  delay(6000); 

  SoftPWMSet(10, 0);//digitalWrite(6, LOW);     screw duruyor
  SoftPWMSet(12, 150);//digitalWrite(7, HIGH);   
  SoftPWMSet(13, 0);//digitalWrite(8, LOW); 

  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 100);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 0);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 100);//digitalWrite(8, LOW); 
  
  delay(3000);


  SoftPWMSet(5, 255);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 255);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 110);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 110);//digitalWrite(8, LOW); 
  delay(3500);


  SoftPWMSet(5, 0);//digitalWrite(5, HIGH);   
  SoftPWMSet(11, 0);//digitalWrite(6, LOW);   


  
  SoftPWMSet(8, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(9, 110);//digitalWrite(8, LOW);   
  
  SoftPWMSet(6, 0);//digitalWrite(7, HIGH);   
  SoftPWMSet(7, 110);//digitalWrite(8, LOW); 

  delay(400);
  
  
}

  Cx = 0;
  if (digitalRead(pin0) == HIGH)
    Cx += 1;
  if (digitalRead(pin1) == HIGH)
    Cx += 2;
  if (digitalRead(pin2) == HIGH)
    Cx += 4;
  if (digitalRead(pin3) == HIGH)
    Cx += 8;
  if (digitalRead(pin4) == HIGH)
    Cx += 16;
  if (digitalRead(pin5) == HIGH)
    Cx += 32;
  if (digitalRead(pin6) == HIGH)
    Cx += 64;
  if (digitalRead(pin7) == HIGH)
    Cx += 128;
  if (digitalRead(pin8) == HIGH)
   Cx += 256;


}



