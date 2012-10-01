#include <iostream>
#include <typeinfo>

using namespace std;

class A{};

class B{};

class C
{
   public:
   char a[100];
};

class D: public A{};

void cStyleCast()
{
   A *a1 = new A();
   cout << "a1 is: " << typeid(a1).name() << endl;
   
   A *a2 = (A*) new B();
   cout << "a2 is: " << typeid(a2).name() << endl;

   A *a3 = (A*) new C();
   cout << "a3 is: " << typeid(a3).name() << endl;
   
   C *c1 = (C*) new A();
   cout << "c1 is: " << typeid(c1).name() << endl;
}

void staticCast()
{
   char a = 0;
   cout << "a: " << static_cast<int>(a) << endl;
   
   int b = 0xFFFF;
   cout << "b: " << static_cast<int>(b) << endl;
   
   a = static_cast<char>(b);
   cout << "a: " << static_cast<int>(a) << endl;
   
   
   A* a1 = new A();
   D* d1 = new D();
   A* a2;
   
   a2 = static_cast<A*>(a1);
   a2 = static_cast<A*>(d1);
   
   //a2 = static_cast<A*>(new B());  //Compile error: invalid static_cast 
                                     //from type ‘B*’ to type ‘A*’
}

void dynamicCast()
{
   A* a1 = new A();
   D* d1 = new D();
   A* a2;
   
   a2 = dynamic_cast<A*>(a1);
   a2 = dynamic_cast<A*>(d1);

   //d1 = dynamic_cast<D*>(a2);  //Compile error: cannot dynamic_cast 
                                 //‘a2’ (of type ‘class A*’) to type ‘class D*’ 
                                 //(source type is not polymorphic)
}

void reinterpretCast()
{

}

void constCast()
{

}

int main()
{
   cStyleCast();
   staticCast();
   dynamicCast();
   reinterpretCast();
   constCast();
   return 1;
}
