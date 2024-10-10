#include <Arduino.h>
#include "My_Advance_Motot.h"
#include "commen_function.h"
#include "my_key.h"
#include "my_led.h"

#include "Trigger.h"
#include "my_timer.h"

#include <stdio.h>
#include <stdlib.h>
#include "double_direct_chain.h"
#include "dynamic_chain.h"

volatile uint8_t led_pin_list[4] = {LED_W_PIN,LED_R_PIN,LED_G_PIN,LED_Y_PIN};
uint8_t led_num=sizeof(led_pin_list)/sizeof(led_pin_list[0]);

volatile bool led_Flag[4]={false,false,false,false};

void led_test();
void led_initial();



//初始化LED引脚
void led_initial(){
    
  for(uint8_t i=0;i<led_num;i++)
  {
    pinMode(led_pin_list[i], OUTPUT);
    digitalWrite(led_pin_list[i],LOW);
  }
}

//测试led灯是否正常，全部亮2S后熄灭
void led_test(){
  digitalWrite(led_pin_list[0],HIGH);
  digitalWrite(led_pin_list[1],HIGH);
  digitalWrite(led_pin_list[2],HIGH);
  digitalWrite(led_pin_list[3],HIGH);
  my_delay_ms(2000);;
  digitalWrite(led_pin_list[0],LOW);
  digitalWrite(led_pin_list[1],LOW);
  digitalWrite(led_pin_list[2],LOW);
  digitalWrite(led_pin_list[3],LOW);
}

void led_light_decesion(){
    for(uint8_t i=0;i<led_num;i++){
        digitalWrite(led_pin_list[i],led_Flag[i]);
    }
}

