/* ESP: Timer and interrupts
 * 
 * Austin Brooks
 * 
 * Timer1 compare match
 */

#define ledPin13
//define for each pin
    #define NDOT_B 0x00;//one
    #define NDOT_D 0x80;

    #define NONE_B 0x10;//one
    #define NONE_D 0x20;

    #define NTWO_B 0x1C;//two
    #define NTWO_D 0x50;

    #define NTHREE_B 0x14;//three
    #define NTHREE_D 0x78;
  
    #define NFOUR_B 0x12;//four
    #define NFOUR_D 0x60;

    #define NFIVE_B 0x06;//five
    #define NFIVE_D 0x70;

    #define NSIX_B 0x0E;//six
    #define NSIX_D 0x70;

    #define NSEVEN_B 0x14;//seven
    #define NSEVEN_D 0x20;

    #define NEIGHT_B 0x1E;//eight
    #define NEIGHT_D 0x70;

    #define NNINE_B 0x16;//nine
    #define NNINE_D 0x70;

    #define NZERO_B 0x1E;//zero
    #define NZERO_D 0x30;

unsigned char *portB;
unsigned char *portC;
unsigned char *portD;
int i, j, k, l;
 int sec1;
 
unsigned char *TCCR1A_ESP;
unsigned char *TCCR1B_ESP;
unsigned char *TCNT1H_ESP;
unsigned char *TCNT1L_ESP;
unsigned char *OCR1AH_ESP;
unsigned char *OCR1AL_ESP;
unsigned char *TIMSK1_ESP;

bool flag = 0;

void setup() {
    unsigned char *portDDRB;
  portDDRB = (unsigned char *) 0x24;
  *portDDRB = 0x1F;

  unsigned char *portDDRD;
  portDDRD= (unsigned char *) 0x2A;
  *portDDRD = 0xF0;

  unsigned char *portDDRC;
  portDDRC = (unsigned char *) 0x27;
  *portDDRC = 0xFF;

  portB = (unsigned char *) 0x25;
  portC = (unsigned char *) 0x28;
  portD = (unsigned char *) 0x2B;
  
  //initialize timer1
  noInterrupts(); // disable all interupts


  portDDRB = (unsigned char *) 0x24;

  portB = (unsigned char *) 0x25;

  unsigned char *TCCR1A_ESP;
  TCCR1A_ESP = (unsigned char *) 0x80;
  unsigned char *TCCR1B_ESP;
  TCCR1B_ESP = (unsigned char *) 0x81;
  unsigned char *TCNT1H_ESP;
  TCNT1H_ESP = (unsigned char *) 0x85;
  unsigned char *TCNT1L_ESP;
  TCNT1L_ESP = (unsigned char *) 0x84;
  unsigned char *OCR1AH_ESP;
  OCR1AH_ESP = (unsigned char *) 0x89;
  unsigned char *OCR1AL_ESP;
  OCR1AL_ESP = (unsigned char *) 0x88;
  unsigned char *TIMSK1_ESP;
  TIMSK1_ESP = (unsigned char *) 0x6F;

  //*portDDRB = 0x20;
  
  *TCCR1A_ESP = 0x00;
  *TCCR1B_ESP = 0x00;
  *TCNT1H_ESP = 0x00;
  *TCNT1L_ESP = 0x00;
  *OCR1AH_ESP = 0x00;
  *OCR1AL_ESP = 0x0F;   // compare match register 16mhz/256/2Hz
  *TCCR1B_ESP |= 0x0C;  // CTC mode (Clear Timer on Compare Match) - BIT3
                        // 256 prescaler BIT2
  *TIMSK1_ESP |= 0x02;

  sei();

  interrupts();

}

ISR(TIMER1_COMPA_vect)  // timer compare interrupt service routine
{
  //toggle for PB5
  if(flag == 0)
  {
    *portB |= 0x20;
    flag = 1;
  }
  else
  {
    *portB &= ~0x20;
    flag = 0;
  }
  //digitalWrite (ledPin, digitalRead (ledPin) ^ 1); // toggle LED pin
}
void loop() {

   for (i = 0; i < 60; i++){ 
  *portB = NDOT_B;
  *portD = NDOT_D;
  *portC &= ~0x04;
  MyDelay(250);
  *portC |= 0x04;
  MyDelay(250);
   }
   sec1++;
  if (sec1 == 1){ // using a timer this should be like when TCNT = 60 change 0x01 to 1
  *portB = NONE_B;
  *portD = NONE_D;
  *portC &= ~0x01;
  MyDelay(200);
  //*portC |= 0x01;

    //this section would essentially repeat the process above up until 10 at which time
    //portC 0x02 would then change to one and the sec1 counter would restart....ETC.
  
    }

}
void MyDelay(unsigned long mSec)
{
  volatile unsigned long i;
  unsigned long endT = 1000 * mSec;

  for (i = 0; i < endT; i++);
}
