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


extern int now_area_num;
extern int now_area_group[LIGHT_GATE_NUM+1];


// 创建双向链表,有问题，数组成员无法赋值给节点，但是在MinWG中却可以，解决办法“手动赋值”
struct DD_list_node * create_DD_list(){

    

    
    //创建一个头节点
    struct DD_list_node * head_p=(struct DD_list_node *)malloc(sizeof(struct DD_list_node));
    if(head_p==NULL)
    {
        return NULL;
    }
    head_p->data=NULL;
    head_p->previous=NULL;
    head_p->next=NULL;

    //创建一个实时指针
    struct DD_list_node * now_p=head_p;//此时，now_p与head指向同一个头节点，无论是对head或是now_p，使用“->”修改内容，都是对节点的修改。

    for(int i=0;i<now_area_num;i++){
        //创建新的数据节点
        struct DD_list_node * newnode = (struct DD_list_node *)malloc(sizeof(struct DD_list_node));
        //存入data
        newnode->data=i;//<******************************************************手动赋值 */
        Serial.println(newnode->data);
        delay(50);
        newnode->previous=now_p;
        newnode->next=NULL;   //此时这个新结点将是尾部的节点

        //正向链接新节点
        now_p->next=newnode;//修改的是头节点，而不是修改head_p,head只是一个指向头节点的指针。

        //更新尾部指针,移动至新的节点
        now_p  = now_p->next;
    }
    
    return head_p;

    

}

//销毁双向链表
void DD_destroy_list(struct DD_list_node * head){
    struct DD_list_node * now_p=head;
    struct DD_list_node * pre_p=NULL;

    while(now_p!=NULL)
    {   
        if(pre_p!=NULL)
        {
            if(pre_p->data!=NULL)
            {
                pre_p->data=NULL;
            }
            
            free(pre_p);
        }
        
        pre_p=now_p;
        now_p=now_p->next;
    }

    //处理下尾巴
    if(pre_p!=NULL)
        {
            if(pre_p->data!=NULL)
            {
                pre_p->data=NULL;
            }
            
            free(pre_p);
        }

}


