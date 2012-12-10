#ifndef POLLY_H
#define POLLY_H
#include "printable.h"
#include "foos.h"

class BaseStuff
{
public:
    BaseStuff(int x) : mX(x) {}
    virtual ~BaseStuff() {}
protected:
    int mX;
private: 
    BaseStuff(); //private version of default ctor to prevent calling it.
};

class Polly : public BaseStuff, public Foo, public IPrintable
{
public: 
    Polly();
    Polly(int x);
    virtual ~Polly();

    virtual std::string toString();
};
#endif