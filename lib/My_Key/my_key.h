#ifndef my_key_h
#define my_key_h

//按键引脚号
#define KEY_1_PIN 12
#define KEY_2_PIN 14
#define KEY_3_PIN 27
#define KEY_4_PIN 26

//按键初始化配置
void key_initial();

//按键的中断触发函数
void key_1_interrupt();
void key_2_interrupt();
void key_3_interrupt();
void key_4_interrupt();


#endif