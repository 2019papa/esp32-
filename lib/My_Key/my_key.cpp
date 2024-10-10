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

volatile uint8_t key_pin_list[4] = {KEY_1_PIN,KEY_2_PIN,KEY_3_PIN,KEY_4_PIN};
uint8_t key_num=sizeof(key_pin_list)/sizeof(key_pin_list[0]);

//单行程光电门出发标志位
volatile bool single_stroke_gate0_Flag=0;
volatile bool single_stroke_gate1_Flag=0;
volatile bool single_stroke_gate2_Flag=0;
volatile bool single_stroke_gate3_Flag=0;
//双行程光电门出发标志位
volatile uint8_t double_stroke_gate0_Flag=0;
volatile uint8_t double_stroke_gate1_Flag=0;
volatile uint8_t double_stroke_gate2_Flag=0;
volatile uint8_t double_stroke_gate3_Flag=0;


extern volatile bool led_Flag[4];
extern DD_list_node * trigger_positon_p;
extern DD_list_node * pre_trigger_positon_p;

int test_value;

//按键初始化
void key_initial();

//按键的中断触发函数
void key_1_interrupt();
void key_2_interrupt();
void key_3_interrupt();
void key_4_interrupt();

void key_initial(){
    //初始化按键引脚
  for(uint8_t i=0;i<key_num;i++)
  {
    pinMode(key_pin_list[i], INPUT_PULLDOWN);
  }
  //初始化按键引脚外部中断，下降沿触发
  attachInterrupt(digitalPinToInterrupt(key_pin_list[0]), key_1_interrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(key_pin_list[1]), key_2_interrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(key_pin_list[2]), key_3_interrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(key_pin_list[3]), key_4_interrupt, FALLING);
  Serial.println("key_initial Done!\n");
  my_delay_ms(10);;
}

void key_1_interrupt()
{
  single_stroke_gate0_Flag=1;
  double_stroke_gate0_Flag+=1;
  led_Flag[0]= !led_Flag[0];

  switch(trigger_positon_p->data){
    case AREA0:{
        pre_trigger_positon_p=trigger_positon_p;
        trigger_positon_p=trigger_positon_p->next;
        //Serial.println(trigger_positon_p->data);
    }
    break;

    case AREA1:{
        pre_trigger_positon_p=trigger_positon_p;
        trigger_positon_p=trigger_positon_p->previous;
        //Serial.println(trigger_positon_p->data);
    } 
    break;

    default:
    {
        pre_trigger_positon_p=pre_trigger_positon_p;
        trigger_positon_p=trigger_positon_p;
    }
        
  }

}



void key_2_interrupt()
{
  single_stroke_gate1_Flag=1;
  double_stroke_gate1_Flag+=1;
  led_Flag[1]= !led_Flag[1];

  switch(trigger_positon_p->data){
    case AREA1:{
        pre_trigger_positon_p=trigger_positon_p;
        trigger_positon_p=trigger_positon_p->next;
        //Serial.println(trigger_positon_p->data);
    }
    break;

    case AREA2:{
        pre_trigger_positon_p=trigger_positon_p;
        trigger_positon_p=trigger_positon_p->previous;
        //Serial.println(trigger_positon_p->data);
    }
    break;

    default:
    {
        pre_trigger_positon_p=pre_trigger_positon_p;
        trigger_positon_p=trigger_positon_p;
    }
  }
}

void key_3_interrupt()
{
  single_stroke_gate2_Flag=1;
  double_stroke_gate2_Flag+=1;
  led_Flag[2]= !led_Flag[2];

  switch(trigger_positon_p->data){
    case AREA2:{
        pre_trigger_positon_p=trigger_positon_p;
        trigger_positon_p=trigger_positon_p->next;
        //Serial.println(trigger_positon_p->data);
    }
        
    break;

    case AREA3:{
        pre_trigger_positon_p=trigger_positon_p;
        trigger_positon_p=trigger_positon_p->previous;
        //Serial.println(trigger_positon_p->data);
    }
    break;

    default:
    {
        pre_trigger_positon_p=pre_trigger_positon_p;
        trigger_positon_p=trigger_positon_p;
    }
  }

}

void key_4_interrupt()
{
  single_stroke_gate3_Flag=1;
  double_stroke_gate3_Flag+=1;
  led_Flag[3]= !led_Flag[3];

  switch(trigger_positon_p->data){
    case AREA3:{
        pre_trigger_positon_p=trigger_positon_p;
        trigger_positon_p=trigger_positon_p->next;
        //Serial.println(trigger_positon_p->data);
    }
    break;

    case AREA4:{
        pre_trigger_positon_p=trigger_positon_p;
        trigger_positon_p=trigger_positon_p->previous;
        //Serial.println(trigger_positon_p->data);
    }
    break;

    default:
    {
        pre_trigger_positon_p=pre_trigger_positon_p;
        trigger_positon_p=trigger_positon_p;
    }
  }
}
