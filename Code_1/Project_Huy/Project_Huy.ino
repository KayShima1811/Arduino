#include "Global.h"
/*------------Macros------------*/
#define FAST      1
#define MEDIUM    2
#define SLOW      3
/*------------------------------*/

/*--------Global Variable-------*/
int ARR_PIN_RL5_OUTPUT[5] = {IN1_RL_PIN, IN2_RL_PIN, IN3_RL_PIN, IN4_RL_PIN, L_AUTO_RL_PIN};
int ARR_PIN_MOTOR_1[4] = {IN1_RL_PIN, IN2_RL_PIN, IN3_RL_PIN, IN4_RL_PIN};
int button_Stage = 0;
int value_sensor_1 = 0;
int signal_transfer_sensor_1;
int signal_transfer_sensor_2;
int value_sensor_2 = 0;
int old_value_sensor_1 = 0;
int count_ON = 0;
int count_Motor_ON = 0;
int count_Motor_OFF = 0;
int old_value_sensor_2;
int count_ON_2 = 0;
unsigned long motorStartTime = 0;
unsigned long motorMStartTime = 0;
unsigned long motorHStartTime = 0;
unsigned long motorStopTime = 0;    
const unsigned long motorRunTime = 1970;    
const unsigned long motorStopTimeDelay = 4000;   
bool motorRunning = false;
unsigned long motor2StartTime = 0; 
unsigned long motor2Duration = 1400;
bool motor2Running = false;
int sensor_2_Stage = 0;
unsigned long Timer1 = 0;
int H_Rain = 550;
int M_Rain = 650;
int L_Rain = 910;
int check_sensor_1 = 0;
bool Check_slow_rain = false;
int count_reset_value = 0;
int save_milis = 0;
int save_milis2 = 0;
int save_milis3 = 0;
bool motorMRunning = false;
bool motorHRunning = false;
bool motorSRunning = false;
unsigned long motorSStartTime = 0; 
int motorF_stage = 0;
int motorM_stage = 0;
int motorS_stage = 0;
int motorOFF_stage = 0;
/*------------------------------*/

/*-------Declare Function-------*/
extern void Setup_Multi_PinMode(int* pin, int number,int status);
extern void Pressed_AUTO();
extern int Sensor_Return_Value(int Pin_Sensor);
extern void Control_Speed_Motor1(int Speed,int* Pin_Motor,int Status);
extern void Off_Motor1(int* Pin_Motor);
extern int Level_Rain(int signal, int value_heavy_rain, int value_moderate_rain, int value_little_rain);
/*------------------------------*/

/*-------Init Function-------*/
SimpleKalmanFilter Filter(2, 2, 0.01);
BTS7960 Motor2(LR_EN_PIN, L_PWM_PIN, R_PWM_PIN);
OneButton BT_AUTO(BT_AUTO_PIN, false);
/*------------------------------*/

void setup() {
  Serial.begin(9600);
  /*-----------Setup_OUTPUT------------*/
  Setup_Multi_PinMode(ARR_PIN_RL5_OUTPUT, 5, OUTPUT);
  /*-----------Setup_INPUT-------------*/
  pinMode(R_SENSOR_PIN, INPUT);
  BT_AUTO.attachClick(Pressed_AUTO);
  Off_Motor1(ARR_PIN_MOTOR_1);
}

void loop() {
  BT_AUTO.tick();
  Motor2.Enable();
  if(button_Stage == 1)
  {
    signal_transfer_sensor_1 = Sensor_Return_Value(F_SENSOR_PIN);
    signal_transfer_sensor_1 = Filter.updateEstimate((float)signal_transfer_sensor_1);
    value_sensor_1 = Level_Rain(signal_transfer_sensor_1, H_Rain, M_Rain, L_Rain);

    value_sensor_2 = Sensor_Return_Value(R_SENSOR_PIN);
    
    // if( (unsigned long) (millis() - Timer1) > 300 )
    // {
    //   if (old_value_sensor_1 != value_sensor_1)
    //   {
    //     Off_Motor1(ARR_PIN_MOTOR_1);
    //     old_value_sensor_1 = value_sensor_1;
    //     check_sensor_1 = 0;
    //   }
    //   Timer1 = millis();
    // }
    if(check_sensor_1 < 10)
    {
      check_sensor_1++;
    }
    else
    {
      // Check rainfall sensor 1
      // Serial.print("Value: ");
      // Serial.println(value_sensor_1);
      // switch (value_sensor_1)
      // {
      //   case 1:
      //     if(motorM_stage == 0 && motorS_stage == 0 && motorOFF_stage == 0)
      //     {
      //       // motorF_stage = 1;
      //       Serial.println("1");
      //     }
      //     break;
      //   case 2:
      //     if(motorF_stage == 0 && motorS_stage == 0 && motorOFF_stage == 0)
      //     {
      //       // motorM_stage = 1;
      //       Serial.println("2");
      //     }
      //     break;
      //   case 3:
      //     if(motorF_stage == 0 && motorM_stage == 0 && motorOFF_stage == 0)
      //     {
      //       // motorS_stage = 1;
      //       Serial.println("3");
      //     }
      //     break;
      //   case 4:
      //     if(motorF_stage == 0 && motorM_stage == 0 && motorS_stage == 0)
      //     {
      //       // motorOFF_stage = 1;
      //       Serial.print(motorOFF_stage);
      //       Serial.println(" - 4 ");
      //     }
      //     break;
      //   default:
      //     break;
      // }
      // if(motorF_stage == 1) // chạy nhanh
      // {
      //   // Serial.println("1");
      //   save_milis = 0;
      //   save_milis3 = 0;
      //   if(save_milis2 == 0)
      //     {
      //       motorHStartTime = millis();
      //       motorHRunning = false;
      //       save_milis2 = 1;
      //       Off_Motor1(ARR_PIN_MOTOR_1);
      //     }
      //   if(!motorHRunning)
      //     {
      //       Control_Speed_Motor1(FAST,ARR_PIN_MOTOR_1,LOW);
      //       motorHStartTime = millis(); 
      //       motorHRunning = true;
      //     }
      //     if(motorHRunning && (millis() - motorHStartTime >= 1300))
      //     {
      //       Control_Speed_Motor1(FAST,ARR_PIN_MOTOR_1,HIGH);
      //       motorHRunning = false;
      //       motorF_stage = 0;
      //     }
      //   Serial.println("1-1");
      // }
      // if(motorM_stage == 1) // chạy vừa
      // {
      //   // Serial.println("2");
      //   save_milis = 0;
      //   save_milis2 = 0;
      //   if(save_milis3 == 0)
      //   {
      //     motorMStartTime = millis();
      //     motorMRunning = false;
      //     save_milis3 = 1;
      //     Off_Motor1(ARR_PIN_MOTOR_1);
      //   }
      //   if(!motorMRunning)
      //   {
      //     Control_Speed_Motor1(MEDIUM,ARR_PIN_MOTOR_1,LOW);
      //     motorMStartTime = millis(); 
      //     motorMRunning = true;
      //   }
      //   if(motorMRunning && (millis() - motorMStartTime >= 1130))
      //   {
      //     Control_Speed_Motor1(MEDIUM,ARR_PIN_MOTOR_1,HIGH);
      //     motorMRunning = false;
      //     motorM_stage = 0;
      //   }
      //   Serial.println("2-1");
      // }
      // if(motorSRunning == 1) // chạy chậm
      // {
      //   // Serial.println("3");
      //   save_milis2 = 0;
      //   save_milis3 = 0;
      //   if(save_milis == 0)
      //   {
      //     motorStartTime = millis();
      //     motorStopTime = millis();
      //     motorRunning = false;
      //     save_milis = 1;
      //     Off_Motor1(ARR_PIN_MOTOR_1);
      //   }
      //   if (!motorRunning) 
      //   {
      //     Control_Speed_Motor1(SLOW,ARR_PIN_MOTOR_1,LOW); 
      //     if(millis() - motorStartTime >= motorRunTime)
      //     {
      //       motorRunning = true;
      //       count_Motor_ON = 0;
      //       motorStopTime = millis();
      //     }
      //   } 
      //   else 
      //   {
      //     Control_Speed_Motor1(SLOW,ARR_PIN_MOTOR_1,HIGH);
      //     if (millis() - motorStopTime >= motorStopTimeDelay) 
      //     {
      //       // motorRunning = false;   
      //       count_Motor_OFF = 0;
      //       motorStartTime = millis();
      //       motorSRunning = 0;
      //     }
      //   }
      //   Serial.println("3-1");
      // }
      
      if(motorOFF_stage == 1);
      {
        save_milis = 0;
        save_milis2 = 0;
        save_milis3 = 0;
        Off_Motor1(ARR_PIN_MOTOR_1);
        Serial.print("OFF: ");
        Serial.println(motorOFF_stage);
        motorOFF_stage = 0;
      }
    }
    // // Check rainfall sensor 2
    // if(value_sensor_2 == 0)
    // {
    //   sensor_2_Stage = 1;
    // }
    // if(sensor_2_Stage == 1)
    // {
    //   if(!motor2Running)
    //   {
    //     Motor2.TurnLeft(255);
    //     motor2StartTime = millis(); 
    //     motor2Running = true;
    //     //Serial.println("RUN");
    //   }
    //   if(motor2Running && (millis() - motor2StartTime >= motor2Duration))
    //   {
    //     Motor2.Stop();
    //     motor2Running = false;
    //     sensor_2_Stage = 0;
    //     //Serial.println("STOP");
    //   }
    // }
  }
}
