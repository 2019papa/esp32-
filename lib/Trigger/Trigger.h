#ifndef trigger_h
#define trigger_h

#define LIGHT_GATE_NUM 4
#define REAL_AREA_NUM 5

//扳机行程模式
//单行程
#define SINGLE_STROKE 0
//双行程
#define DOUBLE_STROKE 1

//开火模式
//单发
#define ONE_SHOOT   0
//二连发
#define TWO_SHOOT   1
//三连单发
#define THREE_SHOOT 2


//默认参数数值
//默认的开火门
#define INITIAL_FIRE_GATE 2
//默认的初始区域
#define INITIAL_AREA_HEAD 0
//默认的末尾区域
#define INITIAL_AREA_TAIL 4
//默认扳机行程
#define INITIAL_TRIGGER_STROKE SINGLE_STROKE
//默认开火模式
#define INITIAL_SHOOT_MODE ONE_SHOOT

//光电门 (4个门)
#define GATE0 0
#define GATE1 1
#define GATE2 2
#define GATE3 3

//区域 (5个区域)
#define AREA0 0
#define AREA1 1
#define AREA2 2
#define AREA3 3
#define AREA4 4

//开火状态
#define CEASE_FIRE 0//熄火
#define OPEN_FIRE  1//开火

//枪的工作状态对应的角度
#define GUN_FIRING_DEGREE 90 //开火过程的角度
#define GUN_RECOVERING_DEGREE 270 //恢复过程的角度

//用户设置扳机参数设置。头部检测区域、尾部检测区域；火门；行程模式、射击模式
int user_set_trigger(int user_head_area,int user_tail_area,int user_fire_gate,int user_stroke_mode,int user_shoot_mode);

//扳机初始化
void trigger_begin();

//扳机区域初始化
void trigger_area_initial();

//检测扳机位置
void trigger_position();

//开火判断
void trigger_fire_decesion();

//开火动作
void fire_movement();

#endif