#ifndef PRINTABLE_H
#define PRINTABLE_H
#include <string>

class IPrintable
{
public:
	virtual ~IPrintable() {}
	virtual std::string toString() = 0;
};


class PrintableDefault
{
public: 
	virtual ~PrintableDefault(){}
	virtual std::string toString() = 0;
};
#endif
