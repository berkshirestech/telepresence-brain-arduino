#include <AccelStepper.h>
//download from http://www.airspayce.com/mikem/arduino/AccelStepper/

// Define a stepper and the pins it will use; (Assuming pinModes are set by the AccelStepper library function.)
AccelStepper stepper1(AccelStepper::DRIVER, 8, 9);
AccelStepper stepper2(AccelStepper::DRIVER, 11, 12);
int powerpin = 7;
int enable1 = 10;
int enable2 = 13;
int spd = 200;    // The current speed in steps/second
int accel = 150;
volatile int inc = 0;

void setup()
{
  Serial.begin(9600);
  stepper1.setMinPulseWidth(50);
  stepper2.setMinPulseWidth(50);
  stepper1.setMaxSpeed(spd);
  stepper1.setAcceleration(accel);
  stepper2.setMaxSpeed(spd);
  stepper2.setAcceleration(accel);
  pinMode(powerpin, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);

  //THIS WAS FOR THE RELAY - MAY BE USED LATER
  //digitalWrite(powerpin, HIGH);

  //This turns the enablers ON
  digitalWrite(enable1, LOW);
  digitalWrite(enable2, LOW);

  //set timer1 interrupt at 1Hz (1 sec)
  cli();//stop interrupts
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;//15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
}

void loop()
{
  if (Serial.available() > 0)
  { //if any characters available over serial
    char c = Serial.read();

    if (c == 'f')
    { // forward
      stepper1.move(100000);
      stepper2.move(100000);
    } else if (c == 'b')
    { // reverse
      stepper1.move(-100000);
      stepper2.move(-100000);
    } else if (c == 'r')
    { // right
      stepper1.move(-100000);
      stepper2.move(100000);
    } else if (c == 'l')
    { // left
      stepper1.move(100000);
      stepper2.move(-100000);
    } else if (c == 's')
    {
      stopMotor();
    } else if (c == 'h') //'h' for who
    {
      Serial.write('l'); //'l' is for legs!
    }

    if (c != 's')
    {
      //turn enablers for the motor on and reset to prevent shutdown
      digitalWrite(enable1, LOW);
      digitalWrite(enable2, LOW);
      inc = 0;
      TCNT1 = 0;
    }


  }

  //always move the motor
  stepper1.run();
  stepper2.run();
}//loop

void stopMotor() {
  stepper1.stop();
  stepper2.stop();
}


ISR(TIMER1_COMPA_vect)
{ 
  inc++;
  if (inc > 25) //25 secs
  {
    stopMotor();
  }
  if (inc > 30)
  {
    digitalWrite(enable1, HIGH);
    digitalWrite(enable2, HIGH);
  }
}
