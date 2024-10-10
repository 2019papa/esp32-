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

// 定义数据类型
struct list_node
{
    int data;
    struct list_node *next;
    
};



// 创建链表
struct list_node * create_list(int data_group[],int data_num){

    for(int i=0;i<data_num;i++){
        data_group[i]=data_group[i];
    }

    
    //创建一个头节点
    struct list_node * head_p=(struct list_node *)malloc(sizeof(struct list_node));
    if(head_p==NULL)
    {
        return NULL;
    }
    head_p->next=NULL;

    //创建一个尾指针
    struct list_node * tail_p=head_p;//此时，tail_p与head指向同一个头节点，无论是对head或是tail_p，使用“->”修改内容，都是对节点的修改。

    for(int i=0;i<data_num;i++){
        //创建新的数据节点
        struct list_node * newnode = (struct list_node *)malloc(sizeof(struct list_node));
        //存入data
        newnode->data=data_group[i];
        newnode->next=NULL;   //此时这个新结点将是尾部的节点

        //将新节点插入值链表中（链接新节点）
        tail_p->next=newnode;//修改的是头节点，而不是修改head_p,head只是一个指向头节点的指针。

        //更新尾部指针,移动至新的节点
        tail_p=newnode;
    }
    return head_p;

    

}

//读取链表中的所有数据
void printf_all_data(struct list_node * head){
    struct list_node * read_p=head;

    int p_null_flag=0;//判断指针是否到最后一个节点了
    for(read_p=head->next;p_null_flag==0;read_p=read_p->next)
    {
         printf("%d ",read_p->data);
         p_null_flag=read_p->next==NULL?1:0;
    }
}

//获取数据节点的数量
int count_data_node(struct list_node * head){
    int count=0;
    struct list_node * read_p=head;

    int p_null_flag=0;//判断指针是否到最后一个节点了
    for(read_p=head->next;p_null_flag==0;read_p=read_p->next)
    {
         count+=1;
         p_null_flag=read_p->next==NULL?1:0;
    }

    return count;
}

//将所有节点中old_data数值替换为new_data
void replace_by_data(struct list_node * head,int old_data,int new_data){
    struct list_node * now_p=head;

    int p_null_flag=0;//判断指针是否到最后一个节点了
    for(now_p=head->next;p_null_flag==0;now_p=now_p->next)
    {
         now_p->data= now_p->data==old_data ? new_data : now_p->data;
         p_null_flag=now_p->next==NULL?1:0;
    }
}

//插入值为value的节点于第k个数据节点前
void add_node(struct list_node * head , int value , int k){
    struct list_node * now_p=head;//此时的指针
    struct list_node * pre_p=NULL;//上一时刻的指针

    struct list_node * new_node_p=(struct list_node *)malloc(sizeof(struct list_node));//创建一个新的节点
    new_node_p->data=value;//存入数值
    


    int p_null_flag=0;//判断指针是否到最后一个节点了
    int count=0;
    while(count!=k)
    {   
        pre_p=now_p;
        now_p=now_p->next;
        count+=1;
    }

    if(now_p==NULL)
    {
        pre_p->next=new_node_p;
        new_node_p->next=NULL;
    }
    else
    {
        pre_p->next=new_node_p;
        new_node_p->next=now_p;  
    }
        

        
}

//删除所有节点中为old_data的节点
void delete_node_by_data(struct list_node * head,int deleted_data){
    struct list_node * now_p=head->next;//此时的指针，直接进入数据节点
    struct list_node * pre_p=head;//上一时刻的指针
    struct list_node * fur_p=NULL;//上上一时刻的指针

    int p_null_flag=0;//判断指针是否到最后一个节点了

    //用中间指针来判断，所以先走一步，让中间指针进入数据节点。注意：循环里扫不到末尾节点
    while(now_p!=NULL)
    {
        //前进一步
        fur_p=pre_p;
        pre_p=now_p;
        now_p=now_p->next;

        if(pre_p->data==deleted_data)
        {
            //删除对应的节点
            pre_p->next=NULL;
            fur_p->next=now_p;
            //清空该节点内存
            free(pre_p);


            //中间指针弹回上一个有效节点处
            pre_p=fur_p;
        }
    }
    
    //看一下尾巴节点是否要删
    if(pre_p->data==deleted_data){
        
        fur_p->next=NULL;
        free(pre_p);
    }

}

//清空链表数据
void clear_all_data(struct list_node * head){
    struct list_node * read_p=head;

    int p_null_flag=0;//判断指针是否到最后一个节点了
    for(read_p=head->next;p_null_flag==0;read_p=read_p->next)
    {
         if(read_p->data!=NULL)
         {
            read_p->data=NULL;
         }
         p_null_flag=read_p->next==NULL?1:0;
    }
}

//销毁链表
void destroy_list(struct list_node * head){
    struct list_node * now_p=head;
    struct list_node * pre_p=NULL;

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

