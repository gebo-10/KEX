// SystemK.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<unordered_map>
enum TypeName {
    Context,
};
struct MemeryItem
{
    int type;
    short shared_count;
    short weak_count;
};

struct MemeryManager {
    std::unordered_map<void*, MemeryItem> record;
};
void* alloc(TypeName type,int size);
void free(void*);
#define weak  
struct SS
{
    weak int* a;
};
int main()
{
    std::cout << "Hello World!\n";
}
