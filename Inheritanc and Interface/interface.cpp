#include <iostream>
#include "printable.h"
#include "foos.h"

class FooPimple : public Foo
{
public:
	FooPimple() {}
	~FooPimple() {} //non virtual dtor since no one is going to inherit this class. Since impl in .cpp file this can be considered safe to know.
};

void fooFunction(Foo* f)
{
	//do stuff with objects of type Foo
	std::cout << f->GetName() << std::endl;
}

void inheritance()
{
	//When creating an inherited class object, both the baseclass ctor 
	//and the inherited classes ctor is run.
	{
		FooBaar foobar;
	}
	//Also when the object is destructed both the inhertied dtor and the
	//base class dtor is run.

	Foo* foo = new Foo();
	fooFunction(foo);
	delete foo;

	//Since FooBaar inherits the Foo class there is no problem 
	//passing a FooBaar object as a Foo pointer to any one that
	//whants a Foo pointer.
	foo = new FooBaar();
	fooFunction(foo);
	delete foo;
}

void virtualStuff()
{
	FooBaar fooBar;
	Foo* foo = &fooBar;
	//Since GetName is virtual the "correct" implementation
	//in the inherited class is run even if the base type pointer
	//is used when accessing the object.
	std::cout << fooBar.GetName() << std::endl;
	std::cout << foo->GetName() << std::endl;

	//Since NonVirtualGetName is not virtual the base class 
	//implementaion is run instead of the inherited one if a 
	//baseclass pointer is used to access a inheritd type object.
	std::cout << fooBar.NonVirtualGetName() << std::endl;
	std::cout << foo->NonVirtualGetName() << std::endl;
}

void pollymophics()
{
}


class MockPrintable : public IPrintable
{
public:
	MockPrintable(){}
	virtual ~MockPrintable(){}
	virtual std::string toString()
	{
		return "Fake data";
	}
};

void printingFunction(IPrintable& obj)
{
	std::cout << obj.toString() << std::endl;
}

void basicInterface()
{
	//Create a "real" printable object and pass it to the print function
	FooPrint fooPrint;
	printingFunction(fooPrint);
	//What happends is the same as when casting the obj to a IPrintable object
	printingFunction(static_cast<IPrintable&>(fooPrint));

	//It is also possible to create a reference object, eventhough IPrintable is abstract,
	//and pass it to the printable function.
	IPrintable& ip(fooPrint);
	printingFunction(ip);

	//One of the benfits of interfaces is the possibility to exchange the real object
	//with some other implementation, ex for some other platform or with a 
	//mock implementation, ex used for testing.
	//This time passed using a pointer to the interface type, just to show that 
	//it is also a viable option.
	MockPrintable mockObj;
	IPrintable* ipp = &mockObj;
	printingFunction(*ipp);
}

void abstractSpecial()
{
	FooBasePrint print;
	std::cout << print.toString();
}

int main()
{
	inheritance(); std::cout << std::endl;
	virtualStuff(); std::cout << std::endl;

	pollymophics(); std::cout << std::endl;

	basicInterface(); std::cout << std::endl;
	
	abstractSpecial(); std::cout << std::endl;

	return 1;
}
