#include <Arduino.h>

void Setup_Multi_PinMode(int* pin, int number,int status)
{
  for(int i = 0; i < number; i++)
  {
    pinMode(*(pin + i), status);
  }
}

// void Pressed_AUTO(int* LED_stage,int Pin_LED)
// {
//   // if(*LED_stage == 0)
//   // {
//   //   *LED_stage = 1;
//   // }
//   // else
//   // {
//   //   *LED_stage = 0;
//   // }
//   *LED_stage = !(*LED_stage);
//   digitalWrite(Pin_LED, !digitalRead(Pin_LED));
//   delay(100);
// }