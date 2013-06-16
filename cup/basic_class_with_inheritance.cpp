#include <iostream>

using namespace std;

class A 
{
public:
  virtual void Print() {cout << "A::Print\n";}
  virtual ~A() {}
};

class B: public A 
{
public:
  virtual void Print() {cout << "B::Print\n";}
  virtual ~B() {}
};

int main()
{
  A *ptr = new B;
  ptr->Print();
  delete ptr;

  A *obj = NULL;
  A base;
  A& baseRef = base;
  baseRef.Print();
  B derived;

  obj = &base;
  obj->Print();

  obj = &derived;
  obj->Print();

  return 0;
}
