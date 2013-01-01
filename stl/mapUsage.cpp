#include <map>
//#include <vector>
//#include <list>
//#include <set>
//#include <string>
//#include <iostream>
//#include <sstream>
#include <boost\shared_ptr.hpp>
//#include <windows.h>
#include "Foo.h"

using namespace std;

void useMap()
{
	const bool enablePrintouts = false;
    map<int, Foo> dict;
    ///Insert 0 = nill
    dict.insert(pair<int, Foo>(0, Foo("nill", enablePrintouts)));

    ///Insert 1 = alfa
    Foo alfa("alfa", enablePrintouts);
    pair<int, Foo> pairAlfa(1, alfa);
    dict.insert( pairAlfa );

    ///Try to insert an existing key
    dict.insert( pair<int, Foo>(0, Foo("NILL", enablePrintouts)));

    ///Overwrite 1=alfa with 1=NewAlfa
    dict[1] = Foo("NewAlfa", enablePrintouts);

    ///Insert 2=beta using operator[]
    dict[2] = Foo("beta", enablePrintouts);

    ///what does the map contain?
    for(map<int, Foo>::const_iterator it = dict.begin(); it != dict.end(); ++it)
    {
        cout << "Element: " << it->first << "=" << it->second.Name() << endl;
    }
    ///So, 0=nill (not NILL!), 1=NewAlfa, 2=beta...
}

void useMapInDepth()
{
    const bool enablePrintouts = true;
    map<int, Foo> dict;

    ///Insert 0 = nill
    pair<map<int, Foo>::iterator,bool> val = dict.insert( pair<int, Foo>(0, Foo("nill", enablePrintouts)));
    if(val.second) 
        cout << "Did insert new element: " << val.first->first << "=" << val.first->second.Name() << endl;
    else 
        cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second.Name() << endl;

    ///Insert 1 = alfa (this is why so many copies...)
    Foo alfa("alfa", enablePrintouts);
    pair<int, Foo> pairAlfa(1, alfa);
    val = dict.insert( pairAlfa ); //<- one copy to the stack since argument type "by-value"
    cout << "return iterator points to Foo element@" << &(val.first->second) << endl;
    cout << "alfa object@" << &alfa << endl;
    cout << "pairAlfas Foo object@" << &(pairAlfa.second) << endl;
    cout << "map Foo alfa object@" << &dict[1] << endl; //Same as returned iterator
    if(val.second) 
        cout << "Did insert new element: " << val.first->first << "=" <<val.first->second.Name() << endl;
    else 
        cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second.Name() << endl;

    ///Insert does not overwrite an existing key/value pair!
    val = dict.insert(pair<int, Foo>(0, Foo("NILL", enablePrintouts)));
    if(val.second) 
        cout << "Did insert new element: " << val.first->first << "=" <<val.first->second.Name() << endl;
    else 
        cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second.Name() << endl;
    cout << "return iterator points to Foo element@" << &(val.first->second) << endl;
    cout << "map Foo alfa object@" << &dict[0] << endl; //Same as returned iterator


    ///Overwrite 1=alfa with 1=NewAlfa existing value using operator[]
    dict[1] = Foo("NewAlfa", enablePrintouts);
    cout << "Value for key: 1=" << dict[1].Name() << endl;
    cout << "map Foo alfa object@" << &dict[1] << endl; //Same as returned iterator
    cout << "OLD return iterator points to Foo element@" << &(val.first->second) << endl;
    cout << "value of old iterator: " << val.first->first << "=" << val.first->second.Name() << endl;

    ///Insert 2=beta using operator[] without key previously in map
    dict[2] = Foo("beta", enablePrintouts);
    cout << "Value for key: 2=" << dict[2].Name() << endl;
}

template<typename MapType>
//typename MapType::iterator insertOrOverwrite(MapType& map, const typename MapType::value_type& value)
void insertOrOverwrite(MapType& map, const typename MapType::value_type& value)
{
    pair<typename MapType::iterator, bool> val = map.insert(value);
    if(!val.second)
    {
        cout << "Overwriting existing value since key already exists" << endl;
        val.first->second = value.second;
    }
    else
    {
        cout << "Inserting new element" << endl;
    }
    //return val.first;
}
void mapInsertOrOverwrite()
{
    map<int, Foo> dict;
    ///Insert 0 = nill
    dict.insert(pair<int, Foo>(0, Foo("nill")));

    ///Insert 1 = alfa
    Foo alfa("alfa");
    pair<int, Foo> pairAlfa(1, alfa);
    dict.insert( pairAlfa );

    ///Overwrite existing 0 with value NILL
    insertOrOverwrite(dict, pair<int, Foo>(0, Foo("NILL")));    

    ///Overwrite 1=alfa with 1=NewAlfa
    dict[1] = Foo("NewAlfa");

    ///Insert 2=beta without creating temporary default object
    insertOrOverwrite(dict, pair<int, Foo>(2, Foo("beta")));    

    ///what does the map contain?
    for(map<int, Foo>::const_iterator it = dict.begin(); it != dict.end(); ++it)
    {
        cout << "Element: " << it->first << "=" << it->second.Name() << endl;
    }
    ///So, 0=NILL, 1=NewAlfa, 2=beta...
}

void useSmartpointersInMaps()
{
    {
        EnablePrintouts = true;
        typedef boost::shared_ptr<Foo> spFoo;
        map<int, spFoo > smartDict;

        ///Insert 0 = nill
        pair<map<int, spFoo>::iterator,bool> val = smartDict.insert( pair<int, spFoo>(0, spFoo(new Foo("nill"))));
        if(val.second) 
            cout << "Did insert new element: " << val.first->first << "=" << val.first->second->Name() << endl;
        else 
            cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second->Name() << endl;

        ///Insert 1 = alfa (this is why so many copies...)
        spFoo alfa(new Foo("alfa"));
        pair<int, spFoo> pairAlfa(1, alfa);
        val = smartDict.insert( pairAlfa ); //<- one copy to the stack since argument type "by-value"
        cout << "return iterator points to Foo element@" << val.first->second.get() << endl;
        cout << "alfa Foo object@" << alfa.get() << endl;
        cout << "pairAlfas Foo object@" << pairAlfa.second.get() << endl;
        cout << "map Foo alfa object@" << smartDict[1].get() << endl; //Same as returned iterator
        if(val.second) 
            cout << "Did insert new element: " << val.first->first << "=" <<val.first->second->Name() << endl;
        else 
            cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second->Name() << endl;

        ///Insert does not overwrite an existing key/value pair!
        val = smartDict.insert(pair<int, spFoo>(0, spFoo(new Foo("NILL"))));
        if(val.second) 
            cout << "Did insert new element: " << val.first->first << "=" <<val.first->second->Name() << endl;
        else 
            cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second->Name() << endl;
        cout << "return iterator points to Foo element@" << val.first->second.get() << endl;
        cout << "map Foo alfa object@" << smartDict[0].get() << endl; //Same as returned iterator


        ///Overwrite 1=alfa with 1=NewAlfa existing value using operator[]
        smartDict[1] = spFoo(new Foo("NewAlfa")); //Does not force dtor of old Foo("alfa") obj since smart_ptr still holds reference to it.
        cout << "Value for key: 1=" << smartDict[1]->Name() << endl;
        cout << "map Foo alfa object@" << smartDict[1].get() << endl; //Same as returned iterator
        cout << "OLD return iterator points to Foo element@" << val.first->second.get() << endl;
        cout << "value of old iterator: " << val.first->first << "=" << val.first->second->Name() << endl;

        ///Insert 2=beta using operator[] without key previously in map
        smartDict[2] = spFoo(new Foo("beta"));
        cout << "Value for key: 2=" << smartDict[2]->Name() << endl;
    } //force dtor of all obj in map and the Foo("alfa") on stack.
    EnablePrintouts = false;
}


void findInMultiMap()
{
    multimap<int, Foo> multiFoos;

    ///insert some data
    multiFoos.insert(pair<int, Foo>(0, Foo("nill")));
    multiFoos.insert(pair<int, Foo>(0, Foo("Nill")));
    multiFoos.insert(pair<int, Foo>(0, Foo("NILL")));
    multiFoos.insert(pair<int, Foo>(1, Foo("alfa")));
    multiFoos.insert(pair<int, Foo>(1, Foo("Alfa")));
    multiFoos.insert(pair<int, Foo>(1, Foo("ALFA")));
    multiFoos.insert(pair<int, Foo>(2, Foo("beta")));
    multiFoos.insert(pair<int, Foo>(2, Foo("Beta")));
    multiFoos.insert(pair<int, Foo>(2, Foo("BETA")));
    multiFoos.insert(pair<int, Foo>(3, Foo("Trea")));
    multiFoos.insert(pair<int, Foo>(4, Foo("Fyra")));

    ///find key 1
    multimap<int, Foo>::const_iterator foundKey = multiFoos.find(1);
    cout << "Key " << foundKey->first << "=" << foundKey->second.Name() << endl;

    ///use upper and lower bounds handling key 1
    multimap<int, Foo>::const_iterator firstKey = multiFoos.lower_bound(1);
    cout << "lower_bound -> Key " << firstKey->first << "=" << firstKey->second.Name() << endl;

    multimap<int, Foo>::const_iterator lastKey = multiFoos.upper_bound(1);
    cout << "upper_bound -> Key " << lastKey->first << "=" << lastKey->second.Name() << endl;

    for(multimap<int, Foo>::const_iterator it = firstKey; it != lastKey; ++it)
    {
        cout << "Key " << it->first << "=" << it->second.Name() << endl;
    }

    ///use upper and lower bounds handling key 3
    firstKey = multiFoos.lower_bound(3);
    cout << "lower_bound -> Key " << firstKey->first << "=" << firstKey->second.Name() << endl;

    lastKey = multiFoos.upper_bound(3);
    cout << "upper_bound -> Key " << lastKey->first << "=" << lastKey->second.Name() << endl;

    for(multimap<int, Foo>::const_iterator it = firstKey; it != lastKey; ++it)
    {
        cout << "Key " << it->first << "=" << it->second.Name() << endl;
    }

    ///use equal_range
    pair<multimap<int, Foo>::const_iterator, multimap<int, Foo>::const_iterator> range = multiFoos.equal_range(1);
    cout << "range.first: " << range.first->second.Name() << endl;
    cout << "range.second: " << range.second->second.Name() << endl;
    for(multimap<int, Foo>::const_iterator it = range.first; it != range.second; ++it)
    {
        cout << "Key " << it->first << "=" << it->second.Name() << endl;
    }

    //OR more likely    
    typedef multimap<int, Foo>::const_iterator mapIt;
    for(pair<mapIt, mapIt> range = multiFoos.equal_range(1);
        range.first != range.second; ++range.first)
    {
        cout << "Key " << range.first->first << "=" << range.first->second.Name() << endl;
    }
}

void remove()
{
    map<int, char> intToChar;
    intToChar.insert(pair<int,char>(0,'a'));
    intToChar.insert(pair<int,char>(1,'a'));
    intToChar.insert(pair<int,char>(2,'b'));
    intToChar.insert(pair<int,char>(3,'b'));
    intToChar.insert(pair<int,char>(4,'c'));
    intToChar.insert(pair<int,char>(5,'d'));

    cout << "intToChar.size = " << intToChar.size() << endl;
    for(map<int, char>::const_iterator it = intToChar.begin(); it != intToChar.end(); ++it)
    {
        cout << "intToChar[" << it->first << "]=" << it->second << endl;
    }

    ///remove all entries with value = b
    for(map<int, char>::iterator it = intToChar.begin(); it != intToChar.end();)
    {
        if(it->second == 'b')
        {
            intToChar.erase(it++); //increase first, remove temporary return iterator
        }
        else
        {
            ++it; //dont create any temporary variable in vain.
        }
    }

    cout << "intToChar.size = " << intToChar.size() << endl;
    for(map<int, char>::const_iterator it = intToChar.begin(); it != intToChar.end(); ++it)
    {
        cout << "intToChar[" << it->first << "]=" << it->second << endl;
    }    
}

void freeMemory()
{
    vector<int> ints;

    //insert some data into the vector
    for(int ii = 0; ii < 100; ++ii)
    {
        ints.push_back(ii);
        cout << "ints.size: " << ints.size() << " ints.capacity: " << ints.capacity() << endl;
    }

    ints.erase(ints.begin()+90, ints.end());
    cout << "ints.size: " << ints.size() << " ints.capacity: " << ints.capacity() << endl;

    ints.erase(ints.begin()+80, ints.end());
    cout << "ints.size: " << ints.size() << " ints.capacity: " << ints.capacity() << endl;

    //how to shrink
    vector<int>(ints).swap(ints);
    cout << "ints.size: " << ints.size() << " ints.capacity: " << ints.capacity() << endl;

    //same for clear
    ints.clear();
    cout << "ints.size: " << ints.size() << " ints.capacity: " << ints.capacity() << endl;
    vector<int>().swap(ints);
    cout << "ints.size: " << ints.size() << " ints.capacity: " << ints.capacity() << endl;

    /////////// "The price to pay" ///////////////
    vector<Foo> foos;

    //insert some data into the vector
    Foo dummyData;
    for(int ii = 0; ii < 100; ++ii)
    {
        foos.push_back(dummyData);        
    }

    foos.erase(foos.begin()+10, foos.end());
    EnablePrintouts = true;
    vector<Foo>(foos).swap(foos);
    EnablePrintouts = false;
}

void itterate()
{
    const int nrOfDataElements = 0xfffff;
    vector<Foo> foos;
    foos.reserve(nrOfDataElements);
    //insert some data into the vector
    Foo dummyData;
    for(int ii = 0; ii < nrOfDataElements; ++ii)
    {
        foos.push_back(dummyData);
    }

    Perf perf;
    perf.Start("Iterator using post-operator");
    for(vector<Foo>::iterator it = foos.begin(); it != foos.end(); it++);
    perf.Stop();
    perf.Print();

    perf.Start("Iterator using pre-operator");
    for(vector<Foo>::iterator it = foos.begin(); it != foos.end(); ++it);
    perf.Stop();
    perf.Print();    

    perf.Start("Const iterator using pre-operator");
    for(vector<Foo>::const_iterator it = foos.begin(); it != foos.end(); ++it);
    perf.Stop();
    perf.Print();

    perf.Start("Reverse iterator using pre-operator");
    for(vector<Foo>::reverse_iterator rit = foos.rbegin(); rit != foos.rend(); ++rit);
    perf.Stop();
    perf.Print();

    perf.Start("Const reverse iterator using pre-operator");
    for(vector<Foo>::const_reverse_iterator rit = foos.rbegin(); rit != foos.rend(); ++rit);
    perf.Stop();
    perf.Print();

    Foo* farray = new Foo[nrOfDataElements];
    perf.Start("Array pre-operator");    
    for(int i = 0; i < nrOfDataElements ; i++) { Foo p = farray[i]; }
    perf.Stop();
    perf.Print();
    delete[] farray;

}

void benchmarkInsert()
{
    const int nrOfDataElements = 0xfffff;
    Foo dummyData;

    /* vector */
    vector<int> ivec;
    vector<Foo> fvec;

    Perf perf;
    perf.Start("Insert ints in vector");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        ivec.push_back(ii);
    perf.Stop();
    perf.Print();

    perf.Start("Insert foos in vector");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        fvec.push_back(dummyData);
    perf.Stop();
    perf.Print();

    ivec.clear(); //no shrink!
    fvec.clear(); //no shrink!
    perf.Start("Insert ints in vector, again!");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        ivec.push_back(ii);
    perf.Stop();
    perf.Print();

    perf.Start("Insert foos in vector, again!");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        fvec.push_back(dummyData);
    perf.Stop();
    perf.Print();


    /* list */
    list<int> ilist;
    list<Foo> flist;

    perf.Start("Insert ints in list");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        ilist.push_back(ii);
    perf.Stop();
    perf.Print();

    perf.Start("Insert foos in list");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        flist.push_back(dummyData);
    perf.Stop();
    perf.Print();

    ilist.clear(); //no shrink!
    flist.clear(); //no shrink!
    perf.Start("Insert ints in list, again!");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        ilist.push_back(ii);
    perf.Stop();
    perf.Print();

    perf.Start("Insert foos in list, again!");
    for(int ii = 0; ii < nrOfDataElements; ++ii)
        flist.push_back(dummyData);
    perf.Stop();
    perf.Print();
}

void benchmarkLookup()
{
    const int nrOfDataElements = 0xfffff;    
    vector<int> ivec;
    list<int> ilist;

    for(int ii = 0; ii < nrOfDataElements; ii += 2) //0, 2, 4, 6, 8, 10, 12
    {
        ivec.push_back(ii);
        ilist.push_back(ii);        
    }

    const int oddNumber = 3; //not in list or vector...
    /* vector */
    Perf perf;
    perf.Start("Find ints in vector");    
    std::find(ivec.begin(), ivec.end(), oddNumber);
    perf.Stop();
    perf.Print();

    perf.Start("Find ints in list");
    std::find(ilist.begin(), ilist.end(), oddNumber);
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
    for(int ii = 0; ii < 1000; ++ii) 
    {
        list<int>::const_iterator it = ilist.begin();
        for(int ii = 0; ii < 1000; ++ii) 
            ++it;

        ilist.erase(it);
    }
    perf.Stop();
    perf.Print();
}

int main()
{
    useMap(); cout << endl;
    useMapInDepth(); cout << endl;
    mapInsertOrOverwrite(); cout << endl;
    useSmartpointersInMaps(); cout << endl;

    findInMultiMap(); cout << endl;

    remove(); cout << endl;
    freeMemory(); cout << endl;

    itterate(); cout << endl;

    benchmarkInsert(); cout << endl;
    benchmarkLookup(); cout << endl;
    benchmarkDelete(); cout << endl;

    return 1;
}
