#include "polly.h"
#include <sstream>

Polly::Polly() : BaseStuff(0)
{
}

Polly::Polly(int x) : BaseStuff(x)
{
}

Polly::~Polly()
{
}

std::string Polly::toString()
{
    std::ostringstream os;
    os << "Polly obj, x=" << mX;
    return os.str();
}
