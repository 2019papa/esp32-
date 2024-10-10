#ifndef __DYNAMIC_CHAIN_H__
#define __DYNAMIC_CHAIN_H__




// 初始化链表
struct list_node * create_list(int data_group[],int data_num);

//读取链表中的所有数据
void printf_all_data(struct list_node * head);

//数链表上的数据节点数
int count_data_node(struct list_node * head);

//将所有节点中old_data数值替换为new_data
void replace_by_data(struct list_node * head,int old_data,int new_data);

////插入值为value的节点于第k个数据节点前
void add_node(struct list_node * head , int value , int k);

//删除所有节点中为old_data的节点
void delete_node_by_data(struct list_node * head,int deleted_data);

//清空链表数据
void clear_all_data(struct list_node * head);

//销毁链表
void destroy_list(struct list_node * head);

#endif

