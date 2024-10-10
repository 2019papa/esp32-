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
//hw_timer_t *my_timer = NULL;
hw_timer_t *once_timer=NULL;

//是否到时间的标志位
volatile bool not_tiktak_Flag =1;
//延时的时长变量
uint64_t delay_time_us=1000;

// // 定时器中断处理函数
// void my_timer_interrupt(){
  
// }

//硬件计时器延时函数，单位us
void my_delay_us(uint64_t time_us);

void once_timer_interrupt() {
  not_tiktak_Flag=0;
}


//定时器初始化配置
void timer_initial() {
  // 初始化定时器
  // my_timer = timerBegin(0,80,true);
  once_timer = timerBegin(1, 80, false);

  // 配置定时器
  // timerAttachInterrupt(my_timer,my_timer_interrupt,true);
  timerAttachInterrupt(once_timer, once_timer_interrupt, true);

  //初始化标志位
  not_tiktak_Flag=1;

  // // 定时模式，单位us，只触发一次
  // // timerAlarmWrite(my_timer,1000000,true); 
  // timerAlarmWrite(once_timer, delay_time_us, false);
  // // 启动定时器
  // // timerAlarmEnable(my_timer); 
  // timerAlarmEnable(once_timer);
 
}

void my_delay_us(uint64_t time_us){
  // 定时模式，单位us，只触发一次
  timerAlarmWrite(once_timer, time_us, false);
  
  //初始化标志位
  not_tiktak_Flag=1;
  
  // 启动定时器
  timerAlarmEnable(once_timer);

  while(not_tiktak_Flag);
}

void my_delay_ms(uint64_t time_ms){
  // 定时模式，单位us，只触发一次
  timerAlarmWrite(once_timer, time_ms*1000, false);
  
  //初始化标志位
  not_tiktak_Flag=1;
  
  // 启动定时器
  timerAlarmEnable(once_timer);

  while(not_tiktak_Flag);
}

void my_delay_s(uint64_t time_s){
  // 定时模式，单位us，只触发一次
  timerAlarmWrite(once_timer, time_s*1000*1000, false);
  
  //初始化标志位
  not_tiktak_Flag=1;
  
  // 启动定时器
  timerAlarmEnable(once_timer);

  while(not_tiktak_Flag);
}
