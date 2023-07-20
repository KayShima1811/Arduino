#include <Arduino.h>
#include "Global.h"

extern int button_Stage;

void Setup_Multi_PinMode(int* pin, int number,int status)
{
  for(int i = 0; i < number; i++)
  {
    pinMode(*(pin + i), status);
  }
}

void Pressed_AUTO()
{
  button_Stage = !button_Stage;
  digitalWrite(L_AUTO_RL_PIN, !digitalRead(L_AUTO_RL_PIN));
  Serial.println("AUTO");
}

int Sensor_Return_Value(int Pin_Sensor)
{
  int value_sensor;
  switch (Pin_Sensor)
  {
  case F_SENSOR_PIN:
    value_sensor = analogRead(F_SENSOR_PIN);
    break;
  case R_SENSOR_PIN:
    value_sensor = digitalRead(R_SENSOR_PIN);
    break;
  default:
    break;
  }
  return value_sensor;
}

void Off_Motor1(int* Pin_Motor)
{
  for(int i = 0; i < 4; i++)
  {
    digitalWrite(*(Pin_Motor + i), HIGH);
    delay(1);
  }
}

void Control_Speed_Motor1(int Speed,int* Pin_Motor,int Status)
{
  int delay_1 = 100;
  int delay_2 = 20;
  switch (Speed)
  {
  case 1:// Fast
    digitalWrite(*(Pin_Motor + 3), Status);
    delay(delay_1);
    digitalWrite(*(Pin_Motor + 1), Status);
    delay(delay_2);
    break;
  case 2:// Medium
    digitalWrite(*(Pin_Motor + 0), Status);
    delay(delay_1);
    digitalWrite(*(Pin_Motor + 2), Status);
    delay(delay_2);
    break;
  case 3:// Slow
    digitalWrite(*(Pin_Motor + 0), Status);
    delay(delay_1);
    digitalWrite(*(Pin_Motor + 1), Status);
    delay(delay_2);
    break;
  default:
    break;
  }
}

int Level_Rain(int signal, int value_heavy_rain, int value_moderate_rain, int value_little_rain)
{
  int value_sensor;
  if(signal > 0 && signal < value_heavy_rain)
  {
    value_sensor = 1;
  }
  else if (signal > value_heavy_rain && signal < value_moderate_rain)
  {
    value_sensor = 2;
  }
  else if (signal > value_moderate_rain && signal < value_little_rain) {
    value_sensor = 3;
  }
  else 
  {
    value_sensor = 4;
  }
  return value_sensor;
}