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

extern int now_area_head;
extern int now_area_tail;
extern int now_area_num;
extern int now_area_group[LIGHT_GATE_NUM+1];

extern int now_fire_gate;
extern int now_light_gate_num;
extern int now_light_gate_group;

extern DD_list_node * trigger_positon_p;
extern DD_list_node * first_node_now_area;//链表的表头，不存任何数据
extern DD_list_node * pre_trigger_positon_p;

extern int now_stroke_mode;//默认单行程
extern int now_shoot_mode;//单发模式

void setup() {
  //更改来看门狗的时间!!!,由300ms->3000ms
  //#define CONFIG_ESP_INT_WDT_TIMEOUT_MS 300
  Serial.begin(9600);
  timer_initial();

  trigger_begin();
  Serial.println("trigger initial Done!\n");

  led_initial();
  Serial.println("led initial Done!\n");

  //test
  Serial.println("test\n");
  my_delay_ms(20);
  rotate_degree_8_beat(360);
  my_delay_ms(20);
  Serial.println("display detail information!!!\n");
  my_delay_ms(20);
  Serial.println("now_area_head:");Serial.println(now_area_head);Serial.println("\n");
  my_delay_ms(20);
  Serial.println("now_fire_gate:");Serial.println(now_fire_gate);Serial.println("\n");
  my_delay_ms(20);
  Serial.println("now_area_tail:");Serial.println(now_area_tail);Serial.println("\n");
  my_delay_ms(20);
  Serial.println("now_area_num:");Serial.println(now_area_num);Serial.println("\n");
  my_delay_ms(20);
  Serial.println("\n");
  my_delay_ms(20);

  Serial.println("LinkChain head data:");Serial.println(first_node_now_area->data);Serial.println("\n");
  my_delay_ms(20);

  Serial.println("node_data:");
  my_delay_ms(20);
  while(trigger_positon_p!=NULL){
    Serial.println(trigger_positon_p->data);Serial.println("\n");
    my_delay_ms(20);
    trigger_positon_p=trigger_positon_p->next;
  }
  trigger_positon_p=first_node_now_area->next;
  

  my_delay_ms(20);
  Serial.println("\n");
  my_delay_ms(20);
  Serial.println("now_stroke_mode:");Serial.println(now_stroke_mode);Serial.println("\n");
  my_delay_ms(20);
  Serial.println("now_shoot_mode:");Serial.println(now_shoot_mode);Serial.println("\n");
  my_delay_ms(20);
  Serial.println("now_area_group value:");
  my_delay_ms(20);
  for(int j=0;j<now_area_num;j++){
      now_area_group[j]=now_area_head+j;
      Serial.println(now_area_group[j]);
      my_delay_ms(20);
  }
  Serial.println("-----------");
  my_delay_ms(20);
}

void loop() {
  // put your main code here, to run repeatedly:
  led_light_decesion();
  trigger_fire_decesion();
  Serial.println("-----");
  my_delay_ms(5);
  Serial.printf("now:%d|pre:%d \n",trigger_positon_p->data,pre_trigger_positon_p->data);
  my_delay_ms(5);
  Serial.println("-----");
  my_delay_ms(5);
}

