#include <msp430g2553.h>

#define SEL1 BIT7 //B = P1.7
#define SEL0 BIT3 //A = P1.3
#define trigger1 BIT3 // trigger sensor 1 = P2.3 1CO
#define trigger2 BIT4 // trigger sensor 2 = P2.4 1C1
#define trigger3 BIT7 // trigger sensor 3 = P2.7 1C2
#define echo BIT4 // Echo mux = P1.4

#define PWM1 BIT0 // Motor1 = P2.0
#define PWM2 BIT2 // Motor2 = P2.2
#define PWM3 BIT5 // Motor3 = P2.5

#define PWM (PWM1|PWM2|PWM3)
#define triggers (trigger1|trigger2|trigger3)

#define LED1 BIT0 //Led  P1.0
#define LED2 BIT6 //Led  P1.6


int miliseconds;
int distance[3];
long sensor;

void AcendeLED(int dist, int n);
void liga_motor(int dist, int n);
void IniciaUltra(int i);
void setSel(int n);

int main(void)
{

    WDTCTL = WDTPW + WDTHOLD;

    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
    // Set de clock TA0
    CCTL0 = CCIE;                             // CCR0 interrupt enabled
    CCR0 = 1000;                  // 1us at 1mhz
    TACTL = TASSEL_2 + MC_1;                  // SMCLK, upmode
    CCTL0 = CCIE;                             // CCR0 interrupt enabled

    //Set de clock TA1
    TA1CCR0 = 1000; //PERÍODO DO PWM
    TA1CCTL1 = OUTMOD_7; //MODO DE SAÍDA DO TIMER0_A: RESET/SET
    TA1CCTL0 = OUTMOD_7;
    TA1CCTL2 = OUTMOD_7;
    TA1CTL = TASSEL_2 + MC_1;        //TASSEL_2 -> CLOCK SOURCE: MCLK   MC_1 -> //TIMER COM CONTAGEM PROGRESSIVA DE 0 ATÉ TACCR1

    _BIS_SR(GIE);

    //Seletoras Multiplex
    P1DIR |= SEL1 + SEL0;                            // P1.3 and P1.7 as output for A e B

    //SET Portas sensor
    P1DIR &= ~echo;         // make pin P1.4 input (ECHO)
    P2DIR |= triggers; // P2. 3,4,5 as output
    P2OUT &= ~triggers;
    P2SEL &= ~triggers; //Select pin 1.2 as our PWM output.
    P2SEL2 &= ~triggers;

    // Set motor

    P2DIR |= PWM; //Set pin 1.2 to the output direction.
    P2OUT &= ~PWM;


    // Set LEDs
    P1DIR |= LED1 + LED2;
    P1OUT &= ~LED1;
    P1OUT &= ~LED2;

    volatile unsigned int count = 0;
    while(1)
    {
      for (count = 0; count < 3; count++n){
          setSel(count);
          __delay_cycles(100);
          IniciaUltra(count);
          distance[count] = sensor/58;           // converting ECHO lenght into cm
          AcendeLED(distance[count], count);
          liga_motor(distance[count], count);

      }
    }
}

void setSel(int n){
  switch(n){
      case 0: // BA = 00
          P1OUT &= ~SEL0;
          P1OUT &= ~SEL1;

          break;
      case 1: // BA = 01
          P1OUT |= SEL0;
          P1OUT &= ~SEL1;
          break;
      case 2: // BA = 10
          P1OUT &= ~SEL0;
          P1OUT |= SEL1;
          break;

      default:
          P1OUT |= SEL0;
          P1OUT |= SEL1;
        }

}

void IniciaUltra(int i){
        P1IE &= ~0x01;       // disable interupt
        switch(i){
          case 0:
            P2OUT |= trigger1;          // generate pulse
              break;
          case 1:
            P2OUT |= trigger2;          // generate pulse
              break;
          case 2:
            P2OUT |= trigger3;          // generate pulse
              break;

          default:
            P2OUT &= ~triggers;
        }
        __delay_cycles(10);             // for 10us
        P2OUT &= ~triggers;
        P1IFG = 0x00;                   // clear flag just in case anything happened before
        P1IE |= echo;           // enable interupt on ECHO pin
        P1IES &= ~echo;         // rising edge on ECHO pin
        __delay_cycles(30000);          // delay for 30ms (after this time echo times out if there is no object detected)
}

void AcendeLED(int dist, int n)//Acender LEDs para debug
{
    if (dist <= 15 && dist != 0){
        switch(n){
        case 0:
            P1OUT &= ~LED1;
            P1OUT |=  LED2;

            break;
        case 1:
            P1OUT |=  LED1;
            P1OUT &=  ~LED2;
            break;
        case 2:
            P1OUT |=  LED1;
            P1OUT |=  LED2;
            break;

        default:
            P1OUT &= ~LED1;
            P1OUT &= ~LED2;
        }
    }
    else{
      if (dist > 21)
      {
          P1OUT &= ~LED1;
          P1OUT &= ~LED2;
      }
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if(P1IFG&echo)
        {
          if(!(P1IES&echo))
          {
            TACTL|=TACLR;   // clears timer A
            miliseconds = 0;
            P1IES |= echo;  //Interrupição para falling edge
          }
          else
          {
            sensor = (long)miliseconds*1000 + (long)TAR;    //Calculo do tamanho do Echo

          }
    P1IFG &= ~echo;             //clear flag
    }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
  miliseconds++;
}


void liga_motor(int dist, int n)
{
    if (dist == 100)
        TA1CCR1 = 300; //DUTY CYCLE DO PWM EM 30%
    else if (dist >= 80  && dist < 100)
        TA1CCR1 = 400; //DUTY CYCLE DO PWM EM 40%
    else if (dist >= 60 && dist < 80)
        TA1CCR1 = 500; //DUTY CYCLE DO PWM EM 50%
    else if (dist >= 35 && dist < 60)
        TA1CCR1 = 600; //DUTY CYCLE DO PWM EM 60%
    else if (dist >= 20 && dist < 35)
        TA1CCR1 = 700; //DUTY CYCLE DO PWM EM 70%
    else if (dist < 20 && dist !=0)
        TA1CCR1 = 800; //DUTY CYCLE DO PWM EM 80%
    else
        TA1CCR1 = 0;

    switch(n){
                case 0:
                    //executa o motor
                    if (TA1R >= TA1CCR1)
                        P2OUT &= ~PWM1;
                    else
                        P2OUT |= PWM1;
                  break;
                case 1:
                    //executa o motor
                    if (TA1R >= TA1CCR1)
                        P2OUT &= ~PWM2;
                    else
                        P2OUT |= PWM2;
                  break;
                case 2:
                    //executa o motor
                    if (TA1R >= TA1CCR1)
                        P2OUT &= ~PWM3;
                    else
                        P2OUT |= PWM3;
                  break;
                default:
                    P2OUT &= ~PWM;
              }

    }
