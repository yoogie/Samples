#include <iostream>
#include "foos.h"

Foo::Foo()
{
	std::cout << "ctor for Foo @" << this << std::endl;
}

Foo::~Foo()
{
	std::cout << "dtor for Foo @" << this << std::endl;
}

std::string Foo::GetName()
{
	return "Foo object";
}

std::string Foo::NonVirtualGetName()
{
	return "Foo object";
}

//////////

FooBaar::FooBaar() : mName("FooBaar object")
{
	std::cout << "ctor for FooBaar @" << this << std::endl;
}

FooBaar::FooBaar(std::string name)
{
	std::cout << "ctor for FooBaar @" << this << std::endl;
	mName = name;
}

FooBaar::~FooBaar()
{
	std::cout << "dtor for FooBaar @" << this << std::endl;
}

std::string FooBaar::GetName()
{
	return mName;
}

std::string FooBaar::NonVirtualGetName()
{
	return mName;
}

//////////

FooPrint::FooPrint()
{
}

FooPrint::~FooPrint()
{
}

std::string FooPrint::toString()
{
	return "FooPrint str";
}

//////////

FooBasePrint::FooBasePrint()
{
}

FooBasePrint::~FooBasePrint()
{
}

std::string FooBasePrint::toString()
{
	return PrintableDefault::toString();
}
