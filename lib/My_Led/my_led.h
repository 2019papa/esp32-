#ifndef my_led_h
#define my_led_h

//LED引脚号
#define LED_W_PIN 21
#define LED_R_PIN 19
#define LED_G_PIN 18
#define LED_Y_PIN 5

//测试led灯是否正常，全部亮2S后熄灭
void led_test();
//初始化LED引脚
void led_initial();

//根据led标志位决定亮灭
void led_light_decesion();

#endif