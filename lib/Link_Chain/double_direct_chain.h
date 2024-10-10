#ifndef __DOUBLE_CHAIN_H__
#define __DOUBLE_CHAIN_H__

// 定义双向链表节点数据类型
struct DD_list_node
{
    volatile int data;

    struct DD_list_node *previous;
    struct DD_list_node *next;
};


// 初始化双向链表
struct DD_list_node * create_DD_list();

//销毁双向链表
void DD_destroy_list(struct DD_list_node * head);

#endif