#include <iostream>
#include <typeinfo>

using namespace std;

class PollyBase1
{
public: 
    PollyBase1() : x(0) {}
    int x;
};
class PollyBase2{};
class Polly : public PollyBase1, public PollyBase2{};

class A
{
public:
    A() : value(0){}
    void setValue(int x) { value = x; }
    int value;
};

class B{};

class C
{
public:
    char a[100];
};

class D: public A
{
public:
    void inCorrectCastUsage(int newValue)
    {
        static_cast<A>(*this).setValue(newValue);        
        //would have worked 
        //static_cast<A*>(this)->setValue(newValue);
        // or "correct"
        //A::setValue(newValue);
    }
};

void cStyleCast()
{
    A *a1 = new A();
    cout << "a1 is: " << typeid(a1).name() << endl;

    A *a2 = (A*) new B();
    cout << "a2 is: " << typeid(a2).name() << endl;

    A *a3 = (A*) new C();
    cout << "a3 is: " << typeid(a3).name() << endl;

    A* a4 = new A();
    C* c1 = (C*) a4;
    cout << "c1 is: " << typeid(c1).name() << endl;
    cout << "Real size of a: " << sizeof(*a4) << endl;
    cout << "Size pointed to by c: " << sizeof(*c1) << endl;
}

void staticCast()
{
    char a = 0;
    cout << "a: " << static_cast<int>(a) << endl;

    int b = 0xFFFF;
    cout << "b: " << static_cast<int>(b) << endl;

    a = static_cast<char>(b);
    cout << "a: " << static_cast<int>(a) << endl;

    b = 0x0FFF;
    cout << "b: " << b << endl;
    a = static_cast<char>(b);
    cout << "a: " << static_cast<int>(a) << endl;


    A* a1 = new A();
    D* d1 = new D();
    A* a2;

    a2 = static_cast<A*>(a1);
    a2 = static_cast<A*>(d1);

    //a2 = static_cast<A*>(new B());  //Compile error: invalid static_cast 
    //from type ‘B*’ to type ‘A*’

    //C* c = static_cast<C*>(a1); //Compile error
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
}

void reinterprtCastF(int obj)
{
    reinterpret_cast<A*>(obj)->value = 1;
    //static_cast<A*>(obj)->value = 2;
    //dynamic_cast<A*>(obj)->value = 1;
}
void reinterpretCast()
{
    A a;    
    cout << "a.value: " << a.value << endl;
    reinterprtCastF((int)&a);
    cout << "a.value: " << a.value << endl;
}

void constCastJiffySignature(char* shouldHaveBeenConst)
{
    cout << "only printing this argument, not changing it: " << shouldHaveBeenConst << endl;
}
void constCast()
{
    const char* arg = "some text";
    constCastJiffySignature(const_cast<char*>(arg));

    // constCastJiffySignature(arg); //error C2664: 
    //'constCastJiffySignature' : cannot convert parameter 1 from 'const char *' to 'char *'

    // constCastJiffySignature(reinterpret_cast<char*>(arg)); //error C2440: 
    // 'reinterpret_cast' : cannot convert from 'const char *' to 'char *'
}

void pollymophic()
{
    Polly obj;
    cout << "address of obj: " << &obj << endl;
    cout << " of PollyBase1: " << &static_cast<PollyBase1>(obj) << endl;
    cout << " of PollyBase2: " << &static_cast<PollyBase1>(obj) << endl;
}

void incorrectCastUsage()
{
    D d;
    cout << "d.value" << d.value << endl;
    d.inCorrectCastUsage(4);
    cout << "d.value" << d.value << endl;
}

int main()
{
    cStyleCast();
    staticCast();
    dynamicCast();
    reinterpretCast();
    constCast();

    pollymophic();
    incorrectCastUsage();

    return 1;
}
