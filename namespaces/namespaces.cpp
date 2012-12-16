#include <iostream>
#include "entity.h"

int function(const int x)
{
	return x;
}

namespace localNamespace
{
	int function(const int x)
	{
		return x+1;
	}

	namespace innerNamespace
	{
		int function(const int x)
		{
			return x+2;
		}
	}
}

void callSpecificFunction()
{
	const int x = 0;
	std::cout << "calling with value " << x << ":" << std::endl;
	std::cout << "function = " << function(x) << std::endl;
	std::cout << "localNamespace::function = " << localNamespace::function(x) << std::endl;
	std::cout << "localNamespace::innerNamespace::function = " << localNamespace::innerNamespace::function(x) << std::endl;
}

void localUsing()
{
	using std::cout;
	cout << "This functions does not need to use std::cout to point cout in the std namespace" << std::endl; //NOTE std::endl
}

void localUsingNamspace()
{
	using namespace std;
	cout << "This functions does not need to use std::cout or std::endl to use cout and endl from the std namespace" << endl;
}

void contextUsingNamspace1()
{
	std::cout << "This function is not using any externa namspaces" << std::endl;

	{
		using std::cout;
		cout << "But in this context we know about the std::cout function. (Still need to point out endl to be from namespace std)" << std::endl;

		{
			using namespace std;
			cout << "And in this context we have knowledge about the whole std namespace" << endl;
		}
	}
}

void contextUsingNamspace2Function()
{
	using namespace std;
	cout << "This function knows about the std namspace" << std::endl;
}
void contextUsingNamspace2()
{
	std::cout << "This function does not know about the std namespace, not before calling a function with the using directive." << std::endl;
	contextUsingNamspace2Function();
	std::cout << "And not after" << std::endl;
}

//This example is a bit over constructed.
//In real life example the EntityImpl class would be the same, just refactored, 
//the enhanced toString function would be "newly added". This is to show
//functionality of te forward/nonforward functions with changes in time.
namespace Example
{
	//Example funtion that formats an entity string
	std::string entityToString(const Alfa::BaseEntity& entity)
	{
		return entity.getName();
	}

	namespace ItterationTwo
	{
		//During itteration two someone created an enhanced function...
		std::string entityToString(const Alfa::BaseEntity& entity)
		{
			std::ostringstream os;
			os << entity.getName() << " (" << entity.getUnitId() << ")";
			return os.str();
		}

		void nonForwardFunction(const Example::Alfa::BaseEntity& entity)
		{
			//By explicitly say that there is a entityToString function in the Example namespace
			//this function will be used even if there is a "better" function in a context
			//closer to the class implementation, hence in the Example::ItterationTwo namespace
			//used for ItterationTwoEntity objects.
			std::cout << "Printing object: " << Example::entityToString(entity) << std::endl;
		}
		void forwardFunction(const Example::Alfa::BaseEntity& entity)
		{
			//By telling that there is a function in the Exmple namespace this function _can_
			//be used to print entities, but if there is a function in a "closer"
			// context ex: Example::ItterationTwo::entityToString function this will be used.
			using namespace Example;
			std::cout << "Printing object: " << entityToString(entity) << std::endl;
		}
		void forwardCompatibleNamspaceUsage()
		{
			Example::ItterationOne::EntityImpl itterOneEntity(1, "first itter obj");
			Example::ItterationTwo::EntityImpl itterTwoEntity1(2, "second itter obj");
			Example::ItterationTwo::EntityImpl itterTwoEntity2(3, "second itter obj");

			nonForwardFunction(itterOneEntity);
			nonForwardFunction(itterTwoEntity1);
			nonForwardFunction(itterTwoEntity2);

			forwardFunction(itterOneEntity);
			forwardFunction(itterTwoEntity1);
			forwardFunction(itterTwoEntity2);
		}
	}
}

int main()
{
	callSpecificFunction(); std::cout << std::endl;
	localUsing(); std::cout << std::endl;
	localUsingNamspace(); std::cout << std::endl;
	contextUsingNamspace1(); std::cout << std::endl;
	contextUsingNamspace2(); std::cout << std::endl;

	Example::ItterationTwo::forwardCompatibleNamspaceUsage(); std::cout << std::endl;

	return 0;
}