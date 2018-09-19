 2.
 ```C
 #include <msp430g2553>
 #define LEDS (BIT0|BIT6)
 
 void atraso (volatile unsigned int N)
 {
  while ((N--)>0);
 }
 
 int main (void)
 {
  WDTCTL = WDTPW|WDTHOLD;
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
 
  while (1)
  {
    P1OUT &=~LEDS;
    atraso(30000);
    P1OUT |= LEDS;
    ATRASO (60000);
  
  }
  return 0;
 }
 ```C
 
 ``` ASSEMBLY
 vetor_dec: push R4 ;R4 = i
            clr R4
            mov R14, R13 ;R14=N
            dec R13 ;N-1
 vetor_dec_for: cmp R13, R4
                jge vetor_dec_end
                cmp 2(R15), 0(R15)
                jge vetor_dec_inc
                pop R4
                clr R15
                ret
            
vetor_dec_inc: inc R4
               incd R15
               jmp vetor_dec_for
               
vetor_dec_end: pop R4
               mov #1, R15 
               ret
``` ASSEMBLY
