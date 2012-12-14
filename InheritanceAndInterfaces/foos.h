#ifndef FOO_H
#define FOO_H
#include "printable.h"

class Foo
{
public:
	Foo();
	virtual ~Foo();//virtual dtor to make inheritors destruct correctly if base class reference is used.

	virtual std::string GetName();
	std::string NonVirtualGetName();
};

class FooBaar : public Foo
{
public:
	FooBaar();
	FooBaar(std::string name);
	virtual ~FooBaar();
	
	virtual std::string GetName();
	std::string NonVirtualGetName();

protected:
	std::string mName;
};

class FooPrint : public Foo, public IPrintable
{
public:
	FooPrint();
	virtual ~FooPrint();

	//Implement IPrintable interface functions
	virtual std::string toString();
};

class FooBasePrint : public Foo, public PrintableDefault
{
public:
	FooBasePrint();
	virtual ~FooBasePrint();

	//Implement PrintableDefault abstract function
	virtual std::string toString();
};

class FaultyBaseClass
{
public:
    FaultyBaseClass();
    ~FaultyBaseClass(); //non virtual dtor
};

class FaultyBaseClassInheritor : public FaultyBaseClass
{
public:
    FaultyBaseClassInheritor();
    ~FaultyBaseClassInheritor();
};

#endif
