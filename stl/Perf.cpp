#include "Perf.h"
#include <iostream>

Perf::Perf() : m_whatToMeassure()
{
    QueryPerformanceFrequency(&m_cpuFreq);
    m_start.HighPart = m_start.LowPart = 0;
    m_stop.HighPart = m_stop.LowPart = 0;
}
void Perf::Start(const std::string& whatToMeassure) 
{
    m_whatToMeassure = whatToMeassure;
    QueryPerformanceCounter(&m_start);
}
void Perf::Stop()
{
    QueryPerformanceCounter(&m_stop);
}
void Perf::Print()
{        
    double differance = static_cast<double>(m_stop.QuadPart - m_start.QuadPart);
    std::cout << m_whatToMeassure << ": " << 1000 * (differance / m_cpuFreq.QuadPart) << " ms" << std::endl;
}
