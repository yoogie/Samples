//#include <map>
//#include <vector>
//#include <list>
//#include <set>
#include <string>
//#include <iostream>
//#include <sstream>
//#include <boost\shared_ptr.hpp>
//#include <windows.h>

class Foo
{
public:
    Foo() : m_name("UnNamed"), mEnablePrintouts(false)
    {
    }

	Foo(const std::string& name, bool enablePrintouts) : m_name(name), mEnablePrintouts(enablePrintouts) 
    {
        if (mEnablePrintouts)
            std::cout << "ctor@" << this << " : " << m_name << std::endl; 
    }

    Foo(const Foo& obj) : m_name(obj.Name()), mEnablePrintouts(obj.mEnablePrintouts)
    {
        if (mEnablePrintouts)
            std::cout << "cpy ctor@" << this << " from " << &obj << " : " << m_name << std::endl;
    }

    ~Foo() 
    {
        if (mEnablePrintouts)
            std::cout << "dtor@" << this << " : " << m_name << std::endl; 
    }

    Foo& operator=(const Foo& obj)
    {
        if(this != &obj)
        {
            if (mEnablePrintouts)
                std::cout << "assignement operator called for element @" << this << "(" << m_name << ") assigning from " << &obj << "(" << obj.Name() << ")" << std::endl;
            m_name = obj.Name();
			mEnablePrintouts = obj.mEnablePrintouts;
        }
        return *this;
    }

	std::string Name() const { return m_name; }
	bool mEnablePrintouts;

private:
	std::string m_name;
};
