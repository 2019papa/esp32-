#ifndef my_timer_h
#define my_timer_h


//硬件计时器延时函数，单位us
void my_delay_us(uint64_t time_us);
//硬件计时器延时函数，单位ms
void my_delay_ms(uint64_t time_ms);
//硬件计时器延时函数，单位ms
void my_delay_s(uint64_t time_s);

//定时器初始化配置
void timer_initial();

//定时中断触发函数
void once_timer_interrupt();

#endif