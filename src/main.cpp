//#include <Arduino.h>

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

// void setup() {
//   // put your setup code here, to run once:
// }

// void loop() {
//   // put your main code here, to run repeatedly:
// }

// int main(void)
// {
//     // make the LED pin an output for PORTB5
//     DDRB = 1 << 4;
//     long i = 1;
//     //long rnd = random();
//     int l = rand()%155;
//     while (1)
//     {
//         _delay_us(.75);

//         i++;
//         //long ms =

//         // toggle the LED
//         if (i>0) {
//           //rnd = random();
//           PORTB ^= 1 << 4;
//           i = 1;
//         }
//     }

//     return 0;
// }
int i = 0;
int count = 100;
int f = 34;
bool out = true;
bool isFirst = true;

ISR(TIM0_COMPA_vect)
{
  // static char light = 1;
  // if (!direction) // прямое направление
  // {
  //   if (light < 0x08) light <<= 1;
  //   else light = 0x01;
  // }
  // else // обратное направление
  // {
  //   if (light > 0x01) light >>= 1;
  //   else light = 0x08;
  // }
  i++;
  if (i%2) out = !out;
  if (i >= count)
  {
    //PORTB ^= 1 << 4;
    i = 0;
    //f = (rand()%150/100.0);
    // f++;
    // if (f > 29)
    // {
    //   f = 0;
    // }
    //f = random()%10+9;
    f = ((random()%32)+24);
    count = random()%150+25;
    //f = random_r(32L);
    //f=32+24;
  }

  //PORTB = (PORTB & 0xF0) | light; // Подставляем в младшие 4 бита порта "B" значение переменной light
}

void wait(int tact)
{
  // for (int n = 0; n < tact; n++)
  // {
  // int l = 0;
  // if(tact%2){
  //   while (l<=tact/2)
  // {
  //   _delay_us(2);
  //   l++;
  //   /* code */
  // }
  // }else{
  //   while (l<=tact/2)
  // {
  //   _delay_us(3);
  //   l++;
  //   /* code */
  // }
  // }

  // _delay_us(4);
  // _delay_us(4);

  // switch (tact)
  // {
  // case 0:
  //   _delay_us(7.75);
  //   break;
  // case 1:
  //   _delay_us(8);
  //   break;
  // case 2:
  //   _delay_us(8.25);
  //   break;
  // case 3:
  //   _delay_us(8.5);
  //   break;
  // case 4:
  //   _delay_us(8.75);
  //   break;
  // case 5:
  //   _delay_us(9);
  //   break;
  // case 6:
  //   _delay_us(9.25);
  //   break;
  // case 7:
  //   _delay_us(9.5);
  //   break;
  // case 8:
  //   _delay_us(9.75);
  //   break;
  // case 9:
  //   _delay_us(10);
  //   break;
  // case 10:
  //   _delay_us(10.25);
  //   break;
  // case 11:
  //   _delay_us(10.5);
  //   break;
  // case 12:
  //   _delay_us(10.75);
  //   break;
  // case 13:
  //   _delay_us(11);
  //   break;
  // case 14:
  //   _delay_us(11.25);
  //   break;
  // case 15:
  //   _delay_us(11.5);
  //   break;
  // case 16:
  //   _delay_us(11.75);
  //   break;
  // case 17:
  //   _delay_us(12);
  //   break;
  // case 18:
  //   _delay_us(12.25);
  //   break;
  // case 19:
  //   _delay_us(12.5);
  //   break;
  // case 20:
  //   _delay_us(12.75);
  //   break;
  // case 21:
  //   _delay_us(13);
  //   break;
  // case 22:
  //   _delay_us(13.25);
  //   break;
  // case 23:
  //   _delay_us(13.5);
  //   break;
  // case 24:
  //   _delay_us(13.75);
  //   break;
  // case 25:
  //   _delay_us(14);
  //   break;
  // case 26:
  //   _delay_us(14.25);
  //   break;
  // case 27:
  //   _delay_us(14.5);
  //   break;
  // case 28:
  //   _delay_us(14.75);
  //   break;
  // case 29:
  //   _delay_us(15);
  //   break;
  // default:
  //   _delay_us(15.25);
  //   //_delay_loop_1(5);
  //   break;
  // };

  /* code */
  // }
}

int main(void)
{

  DDRB = 3 << 3;
  // Настройка прерываний по счётчику/таймеру
  TCCR0A = 0x02;                                    // режим подсчета импульсов (сброс при совпадении)
  TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00); // предделитель clk/1024 (101)
  TCNT0 = 0x00;                                     // начальное значение счётчика импульсов
  OCR0A = 0xFF;                                     // максимальный предел счета (0-255)
  TIMSK0 |= (1 << OCIE0A);                          // разрешение прерывания по совпадению со значением регистра OCR0A

  sei(); // Разрешаем прерывания глобально: SREG |= (1<<SREG_I)
  while (1)
  {
    // wait(f);
    _delay_loop_2(f);
    if(out){
      if(isFirst){
        PORTB = 1 <<3;
        isFirst = false;
        //wait(f);
        _delay_loop_2(f);
      }
      PORTB ^= 3 << 3;
    } else {
      PORTB = 0 << 3;
      isFirst = true;
    }


    // int rnd = random()%19;
    // rnd+=22;
    // rnd = rnd;
    // for (long l = 0; l < 400000; l++)
    // {
    //   _delay_loop_2(rnd);
    //   PORTB ^= 1 << 4;
    // }
    // _delay_ms(500);
    
    

  }
}
