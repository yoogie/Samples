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

void foo1(const boost::shared_ptr<Y>& argY)
{
    std::cout << __FUNCTION__ << " argY.use_count: " << argY.use_count() << std::endl;
}

void foo2(boost::shared_ptr<Y> argY)
{
    std::cout << __FUNCTION__ << " argY.use_count: " << argY.use_count() << std::endl;
}

void Arguments()
{
    boost::shared_ptr<Y> yHolder(new Y);
    std::cout << __FUNCTION__ << " yHolder.use_count: " << yHolder.use_count() << std::endl;
    foo1(yHolder);
    std::cout << __FUNCTION__ << " yHolder.use_count: " << yHolder.use_count() << std::endl;
    foo2(yHolder);
    std::cout << __FUNCTION__ << " yHolder.use_count: " << yHolder.use_count() << std::endl;
}

void STLContainer(boost::shared_ptr<X> arg)
{    
    std::vector< boost::shared_ptr<X> > container;
    container.push_back(arg);
    container.push_back(boost::shared_ptr<X>(new X(true)));        
}

void AssignToSmartPtr(boost::shared_ptr<X>& arg)
{
    arg = boost::shared_ptr<X>(new X(true));
}

int main()
{
    ReferenceCounting();
    AttachToMemory();
    StandardSharedPtrCreation();
    AccesingRawPointer();
    Arguments();

    boost::shared_ptr<X> x(new X(true));
    STLContainer(x);


    std::cout << x.get() << std::endl;
    x.reset();
    std::cout << x.get() << std::endl;
    AssignToSmartPtr(x);
    std::cout << x.get() << std::endl;

    char slask;
    std::cin >> slask;

    return 0;
}
