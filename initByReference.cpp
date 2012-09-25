#include "initByReference.h"
#include <iostream>

MainClass::MainClass(Foo& foo) 
: m_foo(foo)
{}

void CorrectInit()
{
    Foo foo;
    MainClass mObj(foo);
}

void InCorrectDeReferenceNull()
{
    Foo* f = 0;
    MainClass mObj(*f); //ERROR de-referencing null pointer!
    std::cout << "mObj.m_foo @" << &mObj.m_foo << std::endl;
}

Foo& IncorrectReturner()
{
    Foo f;
    return f; //ERROR Returning object allocated on stack and then leaving function, hence deleting object returned.
    //This will at least generate compiler warning: 'C4172: returning address of local variable or temporary'
}
void InCorrectReturnLocalObject()
{
    Foo& f = IncorrectReturner();
    std::cout << "f @" << &f << " [" << f.values[0] << f.values[1] << f.values[2] << f.values[3] << f.values[4] << f.values[5] << f.values[6] << f.values[7] << f.values[8] << f.values[9] << "]"<< std::endl;

    int slask[] = {'1','1','1','1','1','1','1','1','1','1'};
    std::cout << "f @" << &f << " [" << f.values[0] << f.values[1] << f.values[2] << f.values[3] << f.values[4] << f.values[5] << f.values[6] << f.values[7] << f.values[8] << f.values[9] << "]"<< std::endl;

    MainClass mObj1(f); //ERROR object allocated on stack, stack then poped.
    MainClass mObj2(IncorrectReturner()); //ERROR object allocated on stack, stack then poped.
}

#if 0
void main()
{
    CorrectInit();
    InCorrectDeReferenceNull();
    InCorrectReturnLocalObject();
}
#endif