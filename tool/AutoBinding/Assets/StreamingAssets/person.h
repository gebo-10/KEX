// header.hpp
#include <vector>
typedef  int * T ;
struct string{

};
enum e1{
  a=3,
  b,
  c
};
enum class e2{
  c,d,e
}

int max(int v,string sign);

class MyClass:public string{
public:
  int field;
  string a;

  MyClass(){}
  MyClass(int a){}
  virtual T method() const = 0;
 
  static const int static_field;
  static string static_method(){
  	return 100;
  }
};

