#ifndef LIB
  #define LIB
  #include <BTS7960.h>
  #include <OneButton.h>
  #include <SimpleKalmanFilter.h>
#endif

#ifndef GLOBAL_VARIABLE
  #define GLOBAL_VARIABLE
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
  #define L_AUTO_RL_PIN  11
  // BTS7960 - OUTPUT
  #define LR_EN_PIN  8
  #define L_PWM_PIN  9
  #define R_PWM_PIN  10
  // Button AUTO - INPUT
  #define BT_AUTO_PIN 12 
  /*------------------------------*/
#endif
