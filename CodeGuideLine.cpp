#include "trimble2.h"
#include <iostream>

using namespace std;

namespace COMPANY
{
    Company::Company(const int time, const TU8 index, const int id)
        : mTime(time)
        , mIndex(index)
        , mId(id)
    {
    }

    Company::~Company()
    {
    }

    int Company::Time() const
    {
        return mTime;
    }
}
