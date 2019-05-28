#include <iostream>
using namespace std;
class X{
  public:
    void foo(){
      cout << "hello im from an X class" << endl;
    }
};
void regularFunction(){
  cout << "I'm just a regular function" << endl;
}
int main(){
  void (*funcptr)();
  funcptr = regularFunction;
  funcptr();
  void (X::*memFunctPtr)() = &X::foo;
  X myObject;
  myObject.*memFunctPtr = regularFunction;
  return 0;

}



