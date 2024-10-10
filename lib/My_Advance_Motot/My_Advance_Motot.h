#ifndef My_Advance_Motot_h
#define My_Advance_Motot_h


//引脚数量
#define AM_NUMBER 4
//电机引脚号
#define AM_IN1 2
#define AM_IN2 4
#define AM_IN3 22
#define AM_IN4 23

//电机每一步的延迟时间
#define AM_DELAY_TIME 1

void Advance_Motor_initial();

//初始化完后，看看电机能不能动的测试函数
void single_four_beat_test();//单四拍
void double_four_beat_test();//双四拍
void eight_beat_test();      //八拍

//断电,防止继续通电使电机发热、烧毁
void cut_power();


//使电机旋转degree角度

//八拍模式，使电机旋转degree角度
void rotate_degree_8_beat(float degree);




#endif