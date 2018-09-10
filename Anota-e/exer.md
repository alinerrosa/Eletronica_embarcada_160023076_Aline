LISTA 06

DIVISÃO SEM SINAL
```C
unsigned int divisao_uns(unsigned int a, unsigned int b)
  {
    unsigned int c=0;
    if (b>0){
    while (b<=a){
      a-=b;
      c++      
      }
    }
    return c;
  }
  ```
``` ASSEMBLY
  ; R15 = a, R14 = b, R4 = c
divisao_uns: push R4; R4=c
  clear R4; c=0
  tst R14 ;testa se b=0
  jz Div_uns_else ; pula se b=0
Div_uns_while:cmp R14, R15 ;compara b e a 
  jl Div_uns_else ;compara se R15 < R14
  sub R14, R15
  inc R4 ;incrementa c
  jump Div_uns_while
Div_uns_else: mov R4, R15
  pop R4
  ret
  
  
  ```
DIVISÃO COM SINAL
```C
int Divisao(int a, int b)
{
  int sinal = 0, c;
  if (a<0)
  {
    a=-a;
    sinal ++;
  }
  if (b<0)
  {
     b=-b;
    sinal ++;
  }
  c = divisao_uns (a,b);
  if (sinal=1)
      c=-c;
  return c;
}
```

```ASSEMBLY
divisao: push R4 ;sinal
         push R5 ;c 
         clr R4  ; sinal =0
divisao_a: cmp #0,R15
           jge divisao_b
           inv R15
           inc R15 ;a=-a
           inc R4 ;sinal++
divisao_b: cmp #0, %14
           jge divisao_c
           inv R14
           inc R14 ;b=-b
           inc R4 :sinal++
divisao_c: call divisao_uns
           mov R15, R5
           cmp #1, R4
           jne divisao_end
           jnr R5
           jnc R5
divisao_end: mov R5, R15
             pop R5
             pop R4
             ret
             
             
```
O RESTO DA DIVISÃO ESTÁ NO A

NÚMEROS PRIMOS

``` C
int primalidade (unsigned int x)
{
  unsigned int d;
  if (x<2)
      return 0;
  if ((x&1)==0) //faz uma máscara em q apenas o ultimo bit é 1 e faz AND, isso mantem apenas o ultimo bit
      return 0;  //retira todos os pares
  d=x/2;
  while (d>2)
  {
    if ((x%d)==0)
      return 0;
    d--;
  }
  return 1; //só dou esse retorno se ja tiver passado por todos os casos anteriores e n tiver sido nenhum deles
}

``` 
``` ASSEMBLY
primalidade: push R4 ;d
             cmp #2, R15 ; x=R15
             jge teste_par
primo_zero: pop R4
            clr R15
            ret
teste_par: mov R15, R14 ;variável para teste
           and #1, R14
           cmp #0, R14
           jeq primo_zero
teste _impar: mov R15, R4
              rra R4 ;d=x/2
prim_while: cmp #2, R4
            jge prim_end
            push R15 ;jogo o r15 na pilha pq a função q chamarei tbm usa o r15
            mov R4, R14
            call resto_uns
            mov R15, R14
            pop R15
            cmp #0, R14
            jeq prim_zero
            dec R4
            jmp prim_while
prim_end: pop R4
          mov #1, R15
          ret
           
``` 
