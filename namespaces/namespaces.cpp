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
    
    int functionCaller(const int x)
    {
        //Calls the localNamespace::function instead of the function 
        //implemented outside of the namespaces since the 
        //localNamespace::function is in the namespace closes to this.
        return function(x);
    }

    namespace innerNamespace
    {
        int function(const int x)
        {
            return x+2;
        }

        int globalFunctionCaller(const int x)
        {
            return ::function(x);
        }
    }
}
int functionCaller(const int x)
{
    return function(x);
}
void callSpecificFunction()
{
    const int x = 0;
    std::cout << "calling with value " << x << ":" << std::endl;
    std::cout << "function = " << function(x) << std::endl;
    std::cout << "localNamespace::function = " << localNamespace::function(x) << std::endl;
    std::cout << "localNamespace::innerNamespace::function = " << localNamespace::innerNamespace::function(x) << std::endl;

    //The function in the closest namespace will aways be the one 
    //called if there are overloaded versions available.
    std::cout << std::endl;
    std::cout << "localNamespace::functionCaller = " << localNamespace::functionCaller(x) << std::endl;

    //How to specify the global namespace
    std::cout << std::endl;
    std::cout << "localNamespace::innerNamespace::globalFunctionCaller = " << localNamespace::innerNamespace::globalFunctionCaller(x) << std::endl;
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

    namespace ItterationOne
    {
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

    }
}

void forwardCompatibleNamspaceUsage()
{
    //This example also applies to things like using the std::swap
    //function. Which should be done using the same method since
    //at some point in time some one might need to overload their
    //own swap function that handles members in some special way
    //and then it is important that there is no code with explicit 
    //calls to std::swap(X,Y); left that overrides this new function.

    //In this example it does not realy matter what itteration of 
    //the entities that are used, using from both just to show that
    //it is possible and how.
    Example::ItterationOne::EntityImpl itterOneEntity(1, "first itter obj");
    Example::ItterationTwo::EntityImpl itterTwoEntity1(2, "second itter obj");
    Example::ItterationTwo::EntityImpl itterTwoEntity2(3, "second itter obj");

    //During itteration one there was only one entityToString function
    //available so both the nonForward compatible function and the 
    //forward compatible one gives the same result
    Example::ItterationOne::nonForwardFunction(itterOneEntity);
    Example::ItterationOne::nonForwardFunction(itterTwoEntity1);
    Example::ItterationOne::nonForwardFunction(itterTwoEntity2);

    Example::ItterationOne::forwardFunction(itterOneEntity);
    Example::ItterationOne::forwardFunction(itterTwoEntity1);
    Example::ItterationOne::forwardFunction(itterTwoEntity2);

    //During itteration two someone wrote the enhanced entityToString
    //function in the ItterationTwo namspace. The Forward compatible
    //function will then use this function instead.
    Example::ItterationTwo::nonForwardFunction(itterOneEntity);
    Example::ItterationTwo::nonForwardFunction(itterTwoEntity1);
    Example::ItterationTwo::nonForwardFunction(itterTwoEntity2);

    Example::ItterationTwo::forwardFunction(itterOneEntity);
    Example::ItterationTwo::forwardFunction(itterTwoEntity1);
    Example::ItterationTwo::forwardFunction(itterTwoEntity2);
}

int main()
{
    callSpecificFunction(); std::cout << std::endl;
    localUsing(); std::cout << std::endl;
    localUsingNamspace(); std::cout << std::endl;
    contextUsingNamspace1(); std::cout << std::endl;
    contextUsingNamspace2(); std::cout << std::endl;

    forwardCompatibleNamspaceUsage(); std::cout << std::endl;

    return 0;
}