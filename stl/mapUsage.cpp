#include <map>
#include <boost\shared_ptr.hpp>
#include "mapUsage.h"
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
    const bool enablePrintouts = true;
    map<int, Foo> dict;
    ///Insert 0 = nill
    dict.insert(pair<int, Foo>(0, Foo("nill", enablePrintouts)));

    ///Insert 1 = alfa
    Foo alfa("alfa", enablePrintouts);
    pair<int, Foo> pairAlfa(1, alfa);
    dict.insert( pairAlfa );

    ///Overwrite existing 0 with value NILL
    insertOrOverwrite(dict, pair<int, Foo>(0, Foo("NILL", enablePrintouts)));    

    ///Overwrite 1=alfa with 1=NewAlfa
    dict[1] = Foo("NewAlfa", enablePrintouts);

    ///Insert 2=beta without creating temporary default object
    insertOrOverwrite(dict, pair<int, Foo>(2, Foo("beta", enablePrintouts)));    

    ///what does the map contain?
    for(map<int, Foo>::const_iterator it = dict.begin(); it != dict.end(); ++it)
    {
        cout << "Element: " << it->first << "=" << it->second.Name() << endl;
    }
    ///So, 0=NILL, 1=NewAlfa, 2=beta...
}

void useSmartpointersInMaps()
{
    const bool enablePrintouts = true;
    {
        typedef boost::shared_ptr<Foo> spFoo;
        map<int, spFoo > smartDict;

        ///Insert 0 = nill
        pair<map<int, spFoo>::iterator,bool> val = smartDict.insert( pair<int, spFoo>(0, spFoo(new Foo("nill", enablePrintouts))));
        if(val.second) 
            cout << "Did insert new element: " << val.first->first << "=" << val.first->second->Name() << endl;
        else 
            cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second->Name() << endl;

        ///Insert 1 = alfa
        spFoo alfa(new Foo("alfa", enablePrintouts));
        pair<int, spFoo> pairAlfa(1, alfa);
        val = smartDict.insert( pairAlfa );
        cout << "return iterator points to Foo element@" << val.first->second.get() << endl;
        cout << "alfa Foo object@" << alfa.get() << endl;
        cout << "pairAlfas Foo object@" << pairAlfa.second.get() << endl;
        cout << "map Foo alfa object@" << smartDict[1].get() << endl; //Same as returned iterator
        if(val.second) 
            cout << "Did insert new element: " << val.first->first << "=" <<val.first->second->Name() << endl;
        else 
            cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second->Name() << endl;

        ///Insert does not overwrite an existing key/value pair!
        val = smartDict.insert(pair<int, spFoo>(0, spFoo(new Foo("NILL", enablePrintouts))));
        if(val.second) 
            cout << "Did insert new element: " << val.first->first << "=" <<val.first->second->Name() << endl;
        else 
            cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second->Name() << endl;
        cout << "return iterator points to Foo element@" << val.first->second.get() << endl;
        cout << "map Foo alfa object@" << smartDict[0].get() << endl; //Same as returned iterator


        ///Overwrite 1=alfa with 1=NewAlfa existing value using operator[]
        smartDict[1] = spFoo(new Foo("NewAlfa", enablePrintouts)); //Does not force dtor of old Foo("alfa") obj since smart_ptr still holds reference to it.
        cout << "Value for key: 1=" << smartDict[1]->Name() << endl;
        cout << "map Foo alfa object@" << smartDict[1].get() << endl; //Same as returned iterator
        cout << "OLD return iterator points to Foo element@" << val.first->second.get() << endl;
        cout << "value of old iterator: " << val.first->first << "=" << val.first->second->Name() << endl;

        ///Insert 2=beta using operator[] without key previously in map
        smartDict[2] = spFoo(new Foo("beta", enablePrintouts));
        cout << "Value for key: 2=" << smartDict[2]->Name() << endl;
    } //force dtor of all obj in map and the Foo("alfa") on stack.
}


void findInMultiMap()
{
    const bool enablePrintouts = false;
    multimap<int, Foo> multiFoos;

    ///insert some data
    multiFoos.insert(pair<int, Foo>(0, Foo("nill", enablePrintouts)));
    multiFoos.insert(pair<int, Foo>(0, Foo("Nill", enablePrintouts)));
    multiFoos.insert(pair<int, Foo>(0, Foo("NILL", enablePrintouts)));
    multiFoos.insert(pair<int, Foo>(1, Foo("alfa", enablePrintouts)));
    multiFoos.insert(pair<int, Foo>(1, Foo("Alfa", enablePrintouts)));
    multiFoos.insert(pair<int, Foo>(1, Foo("ALFA", enablePrintouts)));
    multiFoos.insert(pair<int, Foo>(2, Foo("beta", enablePrintouts)));
    multiFoos.insert(pair<int, Foo>(2, Foo("Beta", enablePrintouts)));
    multiFoos.insert(pair<int, Foo>(2, Foo("BETA", enablePrintouts)));
    multiFoos.insert(pair<int, Foo>(3, Foo("Trea", enablePrintouts)));
    multiFoos.insert(pair<int, Foo>(4, Foo("Fyra", enablePrintouts)));

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

void removeFromMap()
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
