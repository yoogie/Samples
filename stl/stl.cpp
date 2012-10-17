#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

//#include <typeinfo>

using namespace std;

static bool EnablePrintouts = false;
class Foo
{
public:
    Foo() : m_name("UnNamed") 
    {
        if (EnablePrintouts)
            cout << "ctor@" << this << " : " << m_name << endl; 
    }

    Foo(const string& name) : m_name(name) 
    {
        if (EnablePrintouts)
            cout << "ctor@" << this << " : " << m_name << endl; 
    }

    Foo(const Foo& obj) : m_name(obj.Name())
    {
        if (EnablePrintouts)
            cout << "cpy ctor@" << this << " from " << &obj << " : " << m_name << endl;
    }

    ~Foo() 
    {
        if (EnablePrintouts)
            cout << "dtor@" << this << " : " << m_name << endl; 
    }

    Foo& operator=(const Foo& obj)
    {
        if(this != &obj)
        {
            if (EnablePrintouts)
                cout << "assignement operator called for element @" << this << "(" << m_name << ") assigning from " << &obj << "(" << obj.Name() << ")" << endl;
            m_name = obj.Name();
        }
        return *this;
    }

    string Name() const { return m_name; }

private:    
    string m_name;
};

void useMap()
{
    map<int, Foo> dict;
    ///Insert 0 = nill
    dict.insert(pair<int, Foo>(0, Foo("nill")));

    ///Insert 1 = alfa
    Foo alfa("alfa");
    pair<int, Foo> pairAlfa(1, alfa);
    dict.insert( pairAlfa );

    ///Try to insert an existing key
    dict.insert( pair<int, Foo>(0, Foo("NILL")));    

    ///Overwrite 1=alfa with 1=NewAlfa
    dict[1] = Foo("NewAlfa");

    ///Insert 2=beta using operator[]
    dict[2] = Foo("beta");

    ///what does the map contain?
    for(map<int, Foo>::const_iterator it = dict.begin(); it != dict.end(); ++it)
    {
        cout << "Element: " << it->first << "=" << it->second.Name() << endl;
    }
    ///So, 0=nill (not NILL!), 1=NewAlfa, 2=beta...
}

void useMapInDepth()
{
    EnablePrintouts = true;
    map<int, Foo> dict;

    ///Insert 0 = nill
    pair<map<int, Foo>::iterator,bool> val = dict.insert( pair<int, Foo>(0, Foo("nill")));
    if(val.second) 
        cout << "Did insert new element: " << val.first->first << "=" << val.first->second.Name() << endl;
    else 
        cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second.Name() << endl;

    ///Insert 1 = alfa (this is why so many copies...)
    Foo alfa("alfa");
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
    val = dict.insert(pair<int, Foo>(0, Foo("NILL")));
    if(val.second) 
        cout << "Did insert new element: " << val.first->first << "=" <<val.first->second.Name() << endl;
    else 
        cout << "Did not insert new element, key already exists: " << val.first->first << "=" << val.first->second.Name() << endl;
    cout << "return iterator points to Foo element@" << &(val.first->second) << endl;
    cout << "map Foo alfa object@" << &dict[1] << endl; //Same as returned iterator


    ///Overwrite 1=alfa with 1=NewAlfa existing value using operator[]
    dict[1] = Foo("NewAlfa");
    cout << "Value for key: 1=" << dict[1].Name() << endl;
    cout << "map Foo alfa object@" << &dict[1] << endl; //Same as returned iterator
    cout << "OLD return iterator points to Foo element@" << &(val.first->second) << endl;
    cout << "value of old iterator: " << val.first->first << "=" <<val.first->second.Name() << endl;

    ///Insert 2=beta using operator[] without key previously in map
    dict[2] = Foo("beta");
    cout << "Value for key: 2=" << dict[2].Name() << endl;
    
    EnablePrintouts = false;
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

    /////////// "The price to pay" ///////////////
    vector<Foo> foos;

    //insert some data into the vector
    for(int ii = 0; ii < 100; ++ii)
    {
        ostringstream os; 
        os << ii;
        foos.push_back(os.str());        
    }

    foos.erase(foos.begin()+10, foos.end());
    EnablePrintouts = true;
    vector<Foo>(foos).swap(foos);
    EnablePrintouts = false;
}

void itterate()
{
}

void swap()
{
}

void benchmarkInsert()
{
}

void benchmarkLookup()
{
}

void benchmarkDelete()
{
}

int main()
{
    useMap(); cout << endl;
    useMapInDepth(); cout << endl;
    mapInsertOrOverwrite(); cout << endl;

    findInMultiMap();

    remove();
    freeMemory();

    itterate();

    swap();

    benchmarkInsert();
    benchmarkLookup();
    benchmarkDelete();

    return 1;
}
