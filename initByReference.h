#pragma once

class Foo
{
public:
    Foo() : values()
    {        
    }
    ~Foo(){}

    int values[10];
};

class MainClass
{
public:
    MainClass(Foo& foo);
    Foo& m_foo;
};
