#ifndef CASTS_H
#define CASTS_H

class PollyBase1
{
public: 
    PollyBase1() : x(0) {}
    int x;
};

class PollyBase2{};

class Polly : public PollyBase1, public PollyBase2{};

//////

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
        // or just
        //setValue(newValue);
    }
};

#endif