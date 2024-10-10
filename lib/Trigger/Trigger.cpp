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

int now_area_head=INITIAL_AREA_HEAD;
int now_area_tail=INITIAL_AREA_TAIL;
int now_area_num=now_area_tail-now_area_head+1;
int now_area_group[LIGHT_GATE_NUM+1];

int now_fire_gate=INITIAL_FIRE_GATE;
int now_light_gate_num=LIGHT_GATE_NUM;
int now_light_gate_group[LIGHT_GATE_NUM];

DD_list_node * first_node_now_area;//链表的表头，不存任何数据
DD_list_node * trigger_positon_p;//用来确认扳机位置的指针
DD_list_node * pre_trigger_positon_p=NULL;//上一时刻的指针

int now_stroke_mode=INITIAL_TRIGGER_STROKE;//默认单行程
int now_shoot_mode =INITIAL_SHOOT_MODE;//单发模式

volatile bool fire_Flag=CEASE_FIRE;//默认不开火

//单行程光电门出发标志位
extern volatile bool single_stroke_gate0_Flag;
extern volatile bool single_stroke_gate1_Flag;
extern volatile bool single_stroke_gate2_Flag;
extern volatile bool single_stroke_gate3_Flag;
//双行程光电门出发标志位
extern volatile uint8_t double_stroke_gate0_Flag;
extern volatile uint8_t double_stroke_gate1_Flag;
extern volatile uint8_t double_stroke_gate2_Flag;
extern volatile uint8_t double_stroke_gate3_Flag;



//用户设置扳机参数设置。头部检测区域、尾部检测区域；火门；行程模式、射击模式
int user_set_trigger(int user_head_area,int user_tail_area,int user_fire_gate,int user_stroke_mode,int user_shoot_mode){
    
    
  
    
    //检测用户设置的参数是否合适
    if(user_tail_area > user_head_area && user_tail_area > user_fire_gate && user_head_area >= user_fire_gate){
        //更新变量
        now_area_tail=user_tail_area;
        now_area_head=user_head_area;
        now_area_num=(now_area_tail-now_area_head)+1;

        now_fire_gate=user_fire_gate;
        now_light_gate_num=now_area_tail-now_area_head;//能够触发检测的门数量

        //根据新的变量产生相关数组
        //产生新的检测区域组
        for(int j=0;j<now_area_num;j++){
            now_area_group[j]=now_area_head+j;
        }
        
        //产生新的光电门组
        for(int i=0;i<now_light_gate_num;i++){
            now_light_gate_group[i]=now_area_head+i;
        }
    }
    else 
        return 0;

    //检测扳机、射击模式
    if(user_stroke_mode>=0 && user_stroke_mode<1 && user_shoot_mode>=0 && user_shoot_mode<2)
    {
        now_stroke_mode=user_stroke_mode;
        now_shoot_mode =user_shoot_mode ;
    }
    else
        return 1;

}

//扳机初始化
void trigger_begin(){
    //光电门初始化---暂用按键代替
    key_initial();

    //电机初始化
    Advance_Motor_initial();

    //初始化用户参数
    user_set_trigger(now_area_head,now_area_tail,now_fire_gate,now_stroke_mode,now_shoot_mode);
    Serial.println("User setting done!\n");

    //初始化链表、指针
    trigger_area_initial();
    Serial.println("Linkchain creation done!\n");
    

}


//扳机区域链表初始化
//异常BUG，链表的创建中，节点无法存入数值。在MinGW中运行却没有问题
void trigger_area_initial(){
    if(first_node_now_area !=NULL){
        DD_destroy_list(first_node_now_area);
    }
    
    first_node_now_area=create_DD_list();//创建链表
    trigger_positon_p=first_node_now_area;

    //手动给节点赋值
    //trigger_positon_p=trigger_positon_p->next;//让位置指针进入数据节点

    // for(int j=0;j<now_area_num;j++){
    //     trigger_positon_p=trigger_positon_p->next;
    //     trigger_positon_p->data=now_area_group[j];
      
    // }
    pre_trigger_positon_p=trigger_positon_p;
    trigger_positon_p=first_node_now_area->next;
        
    

}

//检测扳机位置
void trigger_position();

//开火判断
void trigger_fire_decesion(){
    switch(now_stroke_mode){
        case SINGLE_STROKE://单行程
            switch(now_fire_gate){
                case GATE0:{
                    fire_Flag=(single_stroke_gate0_Flag==1 && trigger_positon_p->data==1 && pre_trigger_positon_p->data==0  )?OPEN_FIRE:CEASE_FIRE;
                    single_stroke_gate0_Flag=0;
                }
                break;

                case GATE1:{
                    fire_Flag=(single_stroke_gate1_Flag==1 && trigger_positon_p->data==2 && pre_trigger_positon_p->data==1  )?OPEN_FIRE:CEASE_FIRE;
                    single_stroke_gate1_Flag=0;
                }
                break;

                case GATE2:{
                    fire_Flag=(single_stroke_gate2_Flag==1 && trigger_positon_p->data==3 && pre_trigger_positon_p->data==2 )?OPEN_FIRE:CEASE_FIRE;
                    single_stroke_gate2_Flag=0;
                }
                break;

                case GATE3:{
                    fire_Flag=(single_stroke_gate3_Flag==1 && trigger_positon_p->data==4 && pre_trigger_positon_p->data==3 )?OPEN_FIRE:CEASE_FIRE;
                    single_stroke_gate3_Flag=0;
                }
                break;

                default:{
                    fire_Flag=CEASE_FIRE;
                    single_stroke_gate0_Flag=0;
                    single_stroke_gate1_Flag=0;
                    single_stroke_gate2_Flag=0;
                    single_stroke_gate3_Flag=0;
                    Serial.println("single stroke mode:now_fire_gate error\n");
                }
                    
            }


        break;

        case DOUBLE_STROKE://双行程
            switch(now_fire_gate){
                case GATE0:{
                    if(double_stroke_gate0_Flag==2){
                        fire_Flag=OPEN_FIRE;
                        double_stroke_gate0_Flag=0;//清零
                    }
                    else{
                        fire_Flag=CEASE_FIRE;
                        
                    }
                }
                break;

                case GATE1:{
                    if(double_stroke_gate1_Flag==2){
                        fire_Flag=OPEN_FIRE;
                        double_stroke_gate1_Flag=0;//清零
                    }
                    else{
                        fire_Flag=CEASE_FIRE;
                        
                    }
                }    
                break;

                case GATE2:{
                    if(double_stroke_gate2_Flag==2){
                        fire_Flag=OPEN_FIRE;
                        double_stroke_gate2_Flag=0;//清零
                    }
                    else{
                        fire_Flag=CEASE_FIRE;
                        
                    }
                }
                break;

                case GATE3:{
                    if(double_stroke_gate3_Flag==2){
                        fire_Flag=OPEN_FIRE;
                        double_stroke_gate3_Flag=0;//清零
                    }
                    else{
                        fire_Flag=CEASE_FIRE;
    
                    }       
                }
                break;

                //异常
                default:{
                    fire_Flag=CEASE_FIRE;
                    Serial.println("double stroke mode:now_fire_gate error\n");
                }
                    
            }


        break;


        default:
            fire_Flag=CEASE_FIRE;
            Serial.println("stroke mode error\n");
    }

    
        //开火动作
    fire_movement();
    

}

//开火动作
void fire_movement(){
if(fire_Flag==OPEN_FIRE){
    fire_Flag=CEASE_FIRE;
    //check_gun_recovering();
    switch(now_shoot_mode){
        case ONE_SHOOT:{
            rotate_degree_8_beat(GUN_FIRING_DEGREE);//发射
            my_delay_ms(5);
            rotate_degree_8_beat(GUN_RECOVERING_DEGREE);//发射
            fire_Flag=CEASE_FIRE;
        }
            
            
        break;

        case TWO_SHOOT:{
            rotate_degree_8_beat(GUN_FIRING_DEGREE);//发射
            delay(5);
            rotate_degree_8_beat(GUN_RECOVERING_DEGREE);//发射
            delay(1000);
            rotate_degree_8_beat(GUN_FIRING_DEGREE);//发射
            delay(5);
            rotate_degree_8_beat(GUN_RECOVERING_DEGREE);//发射
            fire_Flag=CEASE_FIRE;
        }
            
            
        break;

        case THREE_SHOOT:{
            rotate_degree_8_beat(GUN_FIRING_DEGREE);//发射
            delay(5);
            rotate_degree_8_beat(GUN_RECOVERING_DEGREE);//发射
            delay(1000);
            rotate_degree_8_beat(GUN_FIRING_DEGREE);//发射
            delay(5);
            rotate_degree_8_beat(GUN_RECOVERING_DEGREE);//发射
            delay(1000);
            rotate_degree_8_beat(GUN_FIRING_DEGREE);//发射
            delay(5);
            rotate_degree_8_beat(GUN_RECOVERING_DEGREE);//发射
            fire_Flag=CEASE_FIRE;
        }
        break;

        default:{
            fire_Flag=CEASE_FIRE;
            cut_power();
            Serial.println("shoot mode error\n");
        }
    }
}
}

