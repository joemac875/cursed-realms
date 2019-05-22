#include <iostream>
using namespace std;
class A;
class B;
class C;
class D;
class D
{
public:
  void speak(){ cout <<"hello"<<endl;};
  void broken(int * y){*y =5;};
};
class B
{
public:
  D* getSpeaker(){ return &myD;};
  void broken(int * y){myD.broken(y);};
private:
  D myD;
};
class C
{
public:
  void speak(B * myB){
    myB->getSpeaker()->speak();
  };
};
class A
{
  public:
    void broken(int * y){myB.broken(y);};
    void speak(){ myC.speak(&myB);};

  private:
    B myB;
    C myC;

};

int main(){
  int * x;
  A().broken(x);
  return 0;
}
