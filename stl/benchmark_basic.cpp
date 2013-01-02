#include <vector>
#include <list>
#include <algorithm>
#include "Perf.h"

using namespace std;

class Baar
{
public:
    Baar(){}
    ~Baar(){}
};

void itterate()
{
    const int nrOfDataElements = 0xfffff;
    vector<Baar> baars;
    baars.reserve(nrOfDataElements);

    //insert some data into the vector
    Baar dummyData;
    for(int ii = 0; ii < nrOfDataElements; ++ii)
    {
        baars.push_back(dummyData);
    }

    Perf perf;
    perf.Start("Iterator using post-operator");
    for(vector<Baar>::iterator it = baars.begin(); it != baars.end(); it++);
    perf.Stop();
    perf.Print();

    perf.Start("Iterator using pre-operator");
    for(vector<Baar>::iterator it = baars.begin(); it != baars.end(); ++it);
    perf.Stop();
    perf.Print();    

    perf.Start("Const iterator using pre-operator");
    for(vector<Baar>::const_iterator it = baars.begin(); it != baars.end(); ++it);
    perf.Stop();
    perf.Print();

    perf.Start("Reverse iterator using pre-operator");
    for(vector<Baar>::reverse_iterator rit = baars.rbegin(); rit != baars.rend(); ++rit);
    perf.Stop();
    perf.Print();

    perf.Start("Const reverse iterator using pre-operator");
    for(vector<Baar>::const_reverse_iterator rit = baars.rbegin(); rit != baars.rend(); ++rit);
    perf.Stop();
    perf.Print();

    Baar* bArray = new Baar[nrOfDataElements];
    perf.Start("Array pre-operator");    
    for(int i = 0; i < nrOfDataElements ; i++) { Baar p = bArray[i]; }
    perf.Stop();
    perf.Print();
    delete[] bArray;

}

void benchmarkInsert()
{
    const int nrOfDataElements = 0xfffff;
    Baar dummyData;

    /* vector */
    vector<int> ivec;
    vector<Baar> bvec;

    Perf perf;
    perf.Start("Insert ints in vector");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        ivec.push_back(ii);
    perf.Stop();
    perf.Print();

    perf.Start("Insert baars in vector");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        bvec.push_back(dummyData);
    perf.Stop();
    perf.Print();

    ivec.clear(); //no shrink!
    bvec.clear(); //no shrink!
    perf.Start("Insert ints in vector, again!");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        ivec.push_back(ii);
    perf.Stop();
    perf.Print();

    perf.Start("Insert baars in vector, again!");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        bvec.push_back(dummyData);
    perf.Stop();
    perf.Print();


    /* list */
    list<int> ilist;
    list<Baar> blist;

    perf.Start("Insert ints in list");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        ilist.push_back(ii);
    perf.Stop();
    perf.Print();

    perf.Start("Insert baars in list");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        blist.push_back(dummyData);
    perf.Stop();
    perf.Print();

    ilist.clear(); //no shrink!
    blist.clear(); //no shrink!
    perf.Start("Insert ints in list, again!");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        ilist.push_back(ii);
    perf.Stop();
    perf.Print();

    perf.Start("Insert baars in list, again!");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        blist.push_back(dummyData);
    perf.Stop();
    perf.Print();
}

void benchmarkLookup()
{
    const int nrOfDataElements = 0xfffff;    
    vector<int> ivec;
    list<int> ilist;

    for(int ii = 0; ii < nrOfDataElements; ++ii)
    {
        ivec.push_back(2);
        ilist.push_back(2);        
    }

    const int oddNumber = 3; //not in list or vector...
    /* vector */
    Perf perf;
    perf.Start("Find ints in vector");    
    find(ivec.begin(), ivec.end(), oddNumber);
    perf.Stop();
    perf.Print();

    perf.Start("Find ints in list");
    find(ilist.begin(), ilist.end(), oddNumber);
    perf.Stop();
    perf.Print();
}

void benchmarkDelete()
{
    const int nrOfDataElements = 0xfffff;
    vector<int> ivec;
    list<int> ilist;

    for(int ii = 0; ii < nrOfDataElements; ++ii)
    {
        ivec.push_back(ii);
        ilist.push_back(ii);
    }

    /* vector */
    Perf perf;
    perf.Start("Delete from start in vector");
    for(int ii = 0; ii < 1000; ++ii) 
        ivec.erase(ivec.begin());
    perf.Stop();
    perf.Print();

    perf.Start("Delete from end in vector");
    for(int ii = 0; ii < 1000; ++ii) 
        ivec.erase(ivec.end()-1);
    perf.Stop();
    perf.Print();

    perf.Start("Delete from pos 1000 in vector");
    for(int ii = 0; ii < 1000; ++ii) 
        ivec.erase(ivec.begin()+1000);
    perf.Stop();
    perf.Print();

    /* list */
    perf.Start("Delete from start in list");
    for(int ii = 0; ii < 1000; ++ii) 
        ilist.erase(ilist.begin());
    perf.Stop();
    perf.Print();

    perf.Start("Delete from end in list");
    for(int ii = 0; ii < 1000; ++ii)
        ilist.erase(--(ilist.end()));
    perf.Stop();
    perf.Print();

    perf.Start("Delete from pos 1000 in list");
    list<int>::const_iterator it = ilist.begin();
    for(int ii = 0; ii < 1000; ++ii);
    for(int ii = 0; ii < 1000; ++ii)
    {
        ilist.erase(it++);
    }
    perf.Stop();
    perf.Print();
}
