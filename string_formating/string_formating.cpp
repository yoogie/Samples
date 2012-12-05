#include <string>
#include <boost\format.hpp>

class Perf
{
public:
    Perf() : m_whatToMeassure()
    {
        QueryPerformanceFrequency(&m_cpuFreq);
        m_start.HighPart = m_start.LowPart = 0;
        m_stop.HighPart = m_stop.LowPart = 0;
    }
    void Start(const string& whatToMeassure) 
    {
        m_whatToMeassure = whatToMeassure;
        QueryPerformanceCounter(&m_start);
    }
    void Stop()
    {
        QueryPerformanceCounter(&m_stop);
    }
    void Print()
    {        
        double differance = static_cast<double>(m_stop.QuadPart - m_start.QuadPart);
        cout << m_whatToMeassure << ": " << 1000 * (differance / m_cpuFreq.QuadPart) << " ms" << endl;
    }

private:
    string m_whatToMeassure;
    LARGE_INTEGER m_cpuFreq;
    LARGE_INTEGER m_start;
    LARGE_INTEGER m_stop;
};

void use_printf_simple()
{
}

void use_cout_simple()
{
}

void use_vsprintf_simple()
{
}

void use_boostFormat_simple()
{
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
    use_printf_simple(); std::cout << std::endl;
    use_cout_simple(); std::cout << std::endl;
    use_vsprintf_simple(); std::cout << std::endl;
    use_boostFormat_simple(); std::cout << std::endl;

    use_printf_complex(); std::cout << std::endl;
    use_cout_complex(); std::cout << std::endl;
    use_vsprintf_complex(); std::cout << std::endl;
    use_boostFormat_complex(); std::cout << std::endl;

    return 1;
}
