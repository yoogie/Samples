#include <boost\shared_ptr.hpp>
#include <vector>

class Y
{
public:
    Y() : value(0) {}
    ~Y() {}
    int value;
};

class X
{
public:
    X()
        :m_y(new Y())
        , m_printExecutionPath(false)
    {
    }

    X(bool printExecutionPath) 
        : m_y(new Y())
        , m_printExecutionPath(printExecutionPath)
    {
        if(m_printExecutionPath)
        {
            std::cout << "X @" << this << " ctor" << std::endl;
        }
    }

    ~X()
    {
        if(m_printExecutionPath)
        {
            std::cout << "X @" << this << " dtor" << std::endl;
        }
    }

    boost::shared_ptr<Y> m_y;

private:
    bool m_printExecutionPath;
};

// A boost::smart_ptr has a member function for showing how many references the object 
// currently has. This function is only intended for debugging.
// In this function we use the default copy ctor for the X class to create a copy of the 
// original object. In the first code block the copy is created as a reference to the original
// in this case the reference counter is not increased. In the second block the copy is made
// by value, hence the object is an actual copy and the counter is increased.
// In both cases the member smart pointer points to the same value as the original since 
// only the smart pointer object it self is copied in the second code block.
void ReferenceCounting()
{
    X org;
    std::cout << "Before blocks:\torg.use_count:" << org.m_y.use_count() << " org.m_y->value:" << org.m_y->value << std::endl;
    {
        X& cpy(org);
        cpy.m_y->value = 1;
        std::cout << "First block:\torg.use_count:" << org.m_y.use_count() << " org.m_y->value:" << org.m_y->value << std::endl;
    }
    std::cout << "Between blocks:\torg.use_count:" << org.m_y.use_count() << " org.m_y->value:" << org.m_y->value << std::endl;
    {
        X cpy(org);
        cpy.m_y->value = 2;
        std::cout << "Second block:\torg.use_count:" << org.m_y.use_count() << " org.m_y->value:" << org.m_y->value << std::endl;
    }
    std::cout << "After blocks:\torg.use_count:" << org.m_y.use_count() << " org.m_y->value:" << org.m_y->value << std::endl;
}

// Examples of how to (faulty) attach a raw pointer to a shared_ptr object
void AttachToMemory()
{
    const bool printExecutionPath = true;
    X* x = new X(printExecutionPath);
    {
        boost::shared_ptr<X> holder(x);
    }    
    //std::cout << x->m_y->value; //ERROR x has been deleted when holder whent out of scope
    //delete x; //ERROR: 
}

//How to create a shared_ptr object, there is no
// raw pointer availlable to access the X object
// without the smart pointer involved.
void StandardSharedPtrCreation()
{
    boost::shared_ptr<X> first(new X(true));
}

// It is possible to access the raw pointer of an shared_ptr object.
// this is not the intended way of accessing the data, but possible.
void AccesingRawPointer()
{
    boost::shared_ptr<Y> yHolder(new Y());
    yHolder->value = 5;
    std::cout << "Y.value: " << yHolder->value << " Y.value using raw pointer: " << yHolder.get()->value << std::endl;
    yHolder.get()->value = 10;
    std::cout << "Y.value: " << yHolder->value << " Y.value using raw pointer: " << yHolder.get()->value << std::endl;
}

// Passing a shared_ptr as an argument is no different from passing any other object, 
// works as expected both as reference and by value.
void Arguments1(const boost::shared_ptr<Y>& argY)
{
    std::cout << __FUNCTION__ << " argY.use_count: " << argY.use_count() << std::endl;
}
void Arguments2(boost::shared_ptr<Y> argY)
{
    std::cout << __FUNCTION__ << " argY.use_count: " << argY.use_count() << std::endl;
}
void Arguments()
{
    boost::shared_ptr<Y> yHolder(new Y);
    std::cout << __FUNCTION__ << " yHolder.use_count: " << yHolder.use_count() << std::endl;
    Arguments1(yHolder);
    std::cout << __FUNCTION__ << " yHolder.use_count: " << yHolder.use_count() << std::endl;
    Arguments2(yHolder);
    std::cout << __FUNCTION__ << " yHolder.use_count: " << yHolder.use_count() << std::endl;
}

// When an STL container such as std::vector goes out of scope it will destruct all containing 
// objects. By storing shared_ptrs one can therefore make sure that the dynamicaly allocated 
// objects will be destructed as well if the container is the last reference holder to the object.
// The object received to this function as an argument still has a reference outside of the 
// vectors scope and will therefore not be destructed here.
void STLContainer(boost::shared_ptr<X> arg)
{    
    std::vector< boost::shared_ptr<X> > container;
    container.push_back(arg);
    container.push_back(boost::shared_ptr<X>(new X(true)));        
}

// It is valid to compare a shared_ptr with null. Reseting a shared_ptr
// decreases the reference counter by one, hence it destructs the object if
// it reaches zero. It is fully possibly to use a shared_ptr reference as 
// output paramter from a function.
void AssignToSmartPtrAssigner1(boost::shared_ptr<X>& arg)
{
    arg = boost::shared_ptr<X>(new X(true));
}
void AssignToSmartPtrAssigner2(boost::shared_ptr<X>& arg)
{
    arg.reset();
}
void AssignToSmartPtr()
{
    boost::shared_ptr<X> x(new X(true));
    std::cout << x.get() << std::endl;
    x.reset();
    std::cout << x.get() << std::endl;
    AssignToSmartPtrAssigner1(x);
    std::cout << x.get() << std::endl;
    AssignToSmartPtrAssigner2(x);
    std::cout << x.get() << std::endl;
}

void ExceptionThrower()
{
    throw std::exception();
}
void MemLeak()
{
    X* x = new X(true);
    ExceptionThrower();
    std::cout << "This is never printed since the exception will cause an early exit from this function" << std::endl;
    delete x; //Will not be run, i.e memory leak
}
void NoMemLeak()
{
    boost::shared_ptr<X> x(new X(true));
    ExceptionThrower();
    std::cout << "This is never printed since the exception will cause an early exit from this function" << std::endl;
    //No need to wrap 'x' in any try/catch since the shared_ptr will destruct x when leaving context.
}
void EarlyExits()
{
    try
    {
        MemLeak();
    } catch (...) {}
    try
    {
        NoMemLeak();
    } catch (...) {}
}

// It is possible to use a custom delete function instead of calling 'delete'
// on the raw object held by a smart_ptr when leaving scope.
void CustomDeleter(X* x)
{
    std::cout << "Going to delete X object @" << x << std::endl;
    delete x;
}
void CustomDelete()
{
    boost::shared_ptr<X> xHolder(new X(true), CustomDeleter);    
}

#if 1
int main()
{
    ReferenceCounting();
    AttachToMemory();
    StandardSharedPtrCreation();
    AccesingRawPointer();
    Arguments();

    boost::shared_ptr<X> x(new X(true));
    STLContainer(x);

    AssignToSmartPtr();
    EarlyExits();
    CustomDelete();

    char slask;
    std::cin >> slask;

    return 0;
}
#endif
