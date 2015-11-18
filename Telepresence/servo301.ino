/************************************************/
#include <Servo.h>
/************************************************/
Servo myservo;//create servo object to control a servo
Servo myservo2;
/************************************************/

unsigned long S1, S2;
unsigned char* s1 = 2+(unsigned char*)&S1; //00 00 00 00
unsigned char* s2 = 2+(unsigned char*)&S2; //00 00 00 00

int DX=300;
byte symb;

void setup()
{
  
    // initialize the serial communication:
  Serial.begin(9600);
  // initialize the ledPin as an output:
  
  myservo.attach(10);//attachs the servo on pin 9 to servo object
    myservo2.attach(9);//attachs the servo on pin 9 to servo object
    
    S1=0;
    S2=0;
   *s1=60 ;
   *s2=70;
   symb = 'C';
   
   myservo2.write(*s1) ;
   myservo.write(*s2) ;
   
  //myservo2.write(90);//back to 0 degrees 
  //myservo.write(50);
  delay(1000);//wait for a second
}
/*************************************************/
void loop()
{
  // check if data has been sent from the computer:
  if (Serial.available()) {
    
   symb = Serial.read(); 
  }
 switch (symb){
    case 'U': {
         if (*s1 > 0) {S1-=DX;}
         break;
    }
    
    case 'D': {
         if (*s1 < 115) {S1+=DX;}
         break;
    }
    
    case 'L': {
         if (*s2 < 160) {S2+=DX;}
         break;
    }
    
    case 'R': {
         if (*s2 > 0) {S2-=DX;}
         break;
    }
    case 'S': {
         
         break;
    }
        case 'C': {
          /////if (*s1 < 60){S1+=DX;}
          /////if (*s1 > 60){S1-=DX;}
          if (*s2 > 70){S2-=DX;}
          if (*s2 < 70){S2+=DX;}
           ///*s1=60 ;
           ///*s2=70;
         break;
    }
    case 'h': {
    Serial.println("h");
    symb = 'C';
    break;
    }
}
   myservo2.write(*s1) ;
   myservo.write(*s2) ;
  // Serial.print(" ");
 //  Serial.println(S1);
}

/**************************************************/

