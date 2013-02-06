#include <string>
#include <boost\format.hpp>

using namespace std;
#define UseEndl 1


void use_printf_simple()
{
    printf("Hello world\n");
}

void use_cout_simple()
{
#ifdef UseEndl
    cout << "Hello world" << endl;
#else
    cout << "Hello world\n";
#endif
}

void use_vsprintf_simple()
{
    const size_t buffSize = 15;
    char buff[buffSize];
    memset(buff, 0, buffSize);
    vsnprintf(buff, 13, "Hello world\n", NULL);
    cout << buff << endl;

    memset(buff, 0, buffSize);
    vsnprintf(buff, 5, "Hello world\n", NULL);
    cout << buff << endl;

    ////It is till possible to write more than there is room for in the buffer
    ////this would corrupt the stack
    
    //memset(buff, 0, buffSize);
    //vsnprintf(buff, 20, "Hello world, more than 15 long\n", NULL);
    //cout << buff << endl;

    //Safe version _s
    memset(buff, 0, buffSize);
    vsnprintf_s(buff, buffSize, 12, "Hello world\n", NULL);
    cout << buff << endl;

    memset(buff, 0, buffSize);
    vsnprintf_s(buff, buffSize, 5, "Hello world\n", NULL);
    cout << buff << endl;

    ////Trying to print more than there is roome for in the buffer will give a 
    ////debug assertion.

    //memset(buff, 0, buffSize);
    //vsnprintf_s(buff, buffSize, 20, "Hello world, more than 15 long\n", NULL);
    //cout << buff << endl;
}

void use_boostFormat_simple()
{
    //xx ?
    boost::format fmt("Hello world\n", locale::classic());
    cout << fmt.str() << endl;

    //re order printf style parameters
    cout << boost::format("%2% world, %1%\n") % "hello!" % "Hello";

    //Various paramter types
    std::string str("value");
    int x = 3;
    cout << boost::format("1:%1%, 2:%2%, 3:%3%\n") % str % str.c_str() % x;

    ////Missing paramter will throw an exception
    ////cout << boost::format("%1%\n");
}

void use_printf_complex()
{
}

void use_cout_complex()
{
}

void use_vsprintf_complex()
{
}

void use_boostFormat_complex()
{
}

int main()
{
    use_printf_simple(); cout << endl;
    use_cout_simple(); cout << endl;
    use_vsprintf_simple(); cout << endl;
    use_boostFormat_simple(); cout << endl;

    use_printf_complex(); cout << endl;
    use_cout_complex(); cout << endl;
    use_vsprintf_complex(); cout << endl;
    use_boostFormat_complex(); cout << endl;

    return 1;
}
