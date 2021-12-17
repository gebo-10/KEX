#pragma once
class CNode
{
public:
    CNode* pre;
    CNode* next;
    void* data;
};
class CList
{
public:
    CList();//默认构造函数
    ~CList();//析构函数
    void add(void* e);//向链表添加数据
    void remove(void* index);//移除某个结点
    CNode find(int index);//查找结点
    bool isEmpty();//判断是否为空
    int size();//链表长度
private:
    CNode *head;
    CNode *tail;
    int length;
};

