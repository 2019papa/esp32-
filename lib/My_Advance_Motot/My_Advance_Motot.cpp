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

//引脚数
uint8_t AM_IN_pin_num=AM_NUMBER;
//引脚号表
uint8_t AM_IN_pin_list[AM_NUMBER]={AM_IN1,AM_IN2,AM_IN3,AM_IN4};

//电机每一步的延迟时间
uint8_t AM_delay_time=AM_DELAY_TIME;

//初始化配置
void Advance_Motor_initial(){
    
pinMode(AM_IN_pin_list[0],OUTPUT);
pinMode(AM_IN_pin_list[1],OUTPUT);
pinMode(AM_IN_pin_list[2],OUTPUT);
pinMode(AM_IN_pin_list[3],OUTPUT);
cut_power();
Serial.println("Motor done!\n");
my_delay_ms(10);


}

//断电,防止继续通电使电机发热、烧毁
void cut_power(){
for(uint8_t i=0;i<AM_IN_pin_num;i++){
    digitalWrite(AM_IN_pin_list[i], LOW);
}
}

//初始化完后，看看电机能不能动的测试函数
//单四拍
void single_four_beat_test(){
uint8_t now_beat = 0;

for (uint8_t i=0;i<256;i++) {

        //四拍，循环4次
        for(uint8_t j=0;j<4;j++){
            //进一拍
            //对应相通电
            for(uint8_t k=0;k<AM_IN_pin_num;k++){
                k==now_beat ? digitalWrite(AM_IN_pin_list[k], HIGH):digitalWrite(AM_IN_pin_list[k], LOW);
            }
            
            now_beat+=1;
            my_delay_ms(AM_delay_time);

        }

        now_beat=0;
    
}

cut_power();//断电

}

//双四拍
void double_four_beat_test(){

for (int i=0;i<256;i++) 
{

    digitalWrite(AM_IN1, 1);
    digitalWrite(AM_IN2, 1);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 0);
    my_delay_ms(AM_delay_time);

    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 1);
    digitalWrite(AM_IN3, 1);
    digitalWrite(AM_IN4, 0);
    my_delay_ms(AM_delay_time);

    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 1);
    digitalWrite(AM_IN4, 1);
    my_delay_ms(AM_delay_time);

    digitalWrite(AM_IN1, 1);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 1);
    my_delay_ms(AM_delay_time);

}

cut_power();//断电
}

//八拍
void eight_beat_test(){
for (int i=0;i<256;i++) {
    digitalWrite(AM_IN1, 1);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 0);
    my_delay_ms(AM_delay_time);


    digitalWrite(AM_IN1, 1);
    digitalWrite(AM_IN2, 1);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 0);
    my_delay_ms(AM_delay_time);


    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 1);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 0);
    my_delay_ms(AM_delay_time);


    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 1);
    digitalWrite(AM_IN3, 1);
    digitalWrite(AM_IN4, 0);
    my_delay_ms(AM_delay_time);


    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 1);
    digitalWrite(AM_IN4, 0);
    my_delay_ms(AM_delay_time);

    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 1);
    digitalWrite(AM_IN4, 1);
    my_delay_ms(AM_delay_time);

    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 1);
    my_delay_ms(AM_delay_time);


    digitalWrite(AM_IN1, 1);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 1);
    my_delay_ms(AM_delay_time);

    
} 
cut_power();//断电     
}


//使电机旋转degree角度

//八拍模式，使电机旋转degree角度
void rotate_degree_8_beat(float degree){

int AM_step_count=2048/4 * degree/360;
for (int i=0;i<AM_step_count;i++) {
    digitalWrite(AM_IN1, 1);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 0);
    delay(AM_delay_time);


    digitalWrite(AM_IN1, 1);
    digitalWrite(AM_IN2, 1);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 0);
    delay(AM_delay_time);


    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 1);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 0);
    delay(AM_delay_time);


    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 1);
    digitalWrite(AM_IN3, 1);
    digitalWrite(AM_IN4, 0);
    delay(AM_delay_time);

    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 1);
    digitalWrite(AM_IN4, 0);
    delay(AM_delay_time);

    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 1);
    digitalWrite(AM_IN4, 1);
    delay(AM_delay_time);

    digitalWrite(AM_IN1, 0);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 1);
    delay(AM_delay_time);


    digitalWrite(AM_IN1, 1);
    digitalWrite(AM_IN2, 0);
    digitalWrite(AM_IN3, 0);
    digitalWrite(AM_IN4, 1);
    delay(AM_delay_time);

    
} 

cut_power();//断电   
}