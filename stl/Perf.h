#pragma once
#ifndef PERF_H
#define PERF_H

#include <string>
#include <windows.h> //messy but need the LARGE_INTEGER here

class Perf
{
public:
    Perf();
    void Start(const std::string& whatToMeassure);
    void Stop();
    void Print();

private:
    std::string m_whatToMeassure;
    LARGE_INTEGER m_cpuFreq;
    LARGE_INTEGER m_start;
    LARGE_INTEGER m_stop;
};
#endif
