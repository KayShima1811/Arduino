#include <BTS7960.h>
#include <OneButton.h>
#include <SimpleKalmanFilter.h>

/*----------Define Pin----------*/
// Module Relay Motor 1 - OUTPUT
#define IN1_RL_PIN  2
#define IN2_RL_PIN  3
#define IN3_RL_PIN  4
#define IN4_RL_PIN  5
// Front Sensor - INPUT
#define F_SENSOR_PIN  A0
// Rear Sensor - INPUT
#define R_SENSOR_PIN  7
// Module Relay Led AUTO - OUTPUT
#define L_AUTO_RL_PIN  8
// BTS7960 - OUTPUT
#define LR_EN_PIN  9
#define L_PWM_PIN  10
#define R_PWM_PIN  11
// Button AUTO - INPUT
#define BT_AUTO_PIN 12 
/*------------------------------*/

/*--------Global Variable-------*/
int ARR_PIN_RL5_OUTPUT[5] = {IN1_RL_PIN, IN2_RL_PIN, IN3_RL_PIN, IN4_RL_PIN, L_AUTO_RL_PIN};
int button_Stage = 0;
/*------------------------------*/

/*-------Declare Function-------*/
extern void Setup_Multi_PinMode(int* pin, int number,int status);
// extern void Pressed_AUTO(int* LED_stage,int Pin_LED);
/*------------------------------*/

/*-------Init Function-------*/
SimpleKalmanFilter Filter(2, 2, 0.01);
BTS7960 Motor2(LR_EN_PIN, L_PWM_PIN, R_PWM_PIN);
OneButton BT_AUTO(BT_AUTO_PIN, true);
/*------------------------------*/

void setup() {
  Serial.begin(9600);
  /*-----------Setup_OUTPUT------------*/
  Setup_Multi_PinMode(ARR_PIN_RL5_OUTPUT, 5, OUTPUT);
  pinMode(13, OUTPUT);
  /*-----------Setup_INPUT-------------*/
  pinMode(R_SENSOR_PIN, INPUT);
  BT_AUTO.attachClick(Pressed_AUTO);
}

void loop() {
  BT_AUTO.tick();
  Motor2.Enable();
  
  if(button_Stage == 1)
  {
    
  }
}

void Pressed_AUTO()
{
  button_Stage = !button_Stage;
  digitalWrite(13, !digitalRead(13));
}