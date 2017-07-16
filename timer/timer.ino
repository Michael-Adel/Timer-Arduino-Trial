#include <Arduino_FreeRTOS.h>
#include "macros.h"
#include "motordriver.h"
#include "linetracker.h"

int timer1_counter=0;

unsigned int timer1_revs = 0;

void setup()
{
  Serial.begin(9600);
  init_line_tracker();
  //--------------------------timer setup
  noInterrupts();           // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  timer1_counter = 59286;   // preload timer 65536-16MHz/256/2Hz (34286 for 0.5sec) (59286 for 0.1sec)

  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
  
  MotorDriverLeft(200,1);
  MotorDriverRight(200,1);
  delay(200);
}


void loop()
{
  
}


ISR(TIMER1_OVF_vect) {
  
  TCNT1 = timer1_counter;
  timer1_revs++;
  if(timer1_revs == 50) {
    
    int RPM_Counter1 = LineDetectorCounterLeft;
    int RPM_Counter2 = LineDetectorCounterRight;
    Serial.print(" RPMCounter_Left: " );Serial.println((double)RPM_Counter1/8 );
    Serial.print(" RPMCounter_Right: " );Serial.println((double)RPM_Counter2/8 );
   // RPM_Counter1 = 0; 
   // RPM_Counter2 = 0; 
    
    timer1_revs = 0;
  }

}


