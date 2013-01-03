#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

class Sortable
{
public:
    Sortable(int id) : mId(id) {}

    //A bit of an 'odd' impl of < since it returns if id is > just to
    //show the point of an customized operator
    bool operator<(const Sortable& rhs) const
    {
        return mId > rhs.mId;
    }
    
    int mId;

private:
    Sortable();
};


void useASet()
{
    //Insert some random ints into a set.
    std::set<int> ints;

    ints.insert(3);
    ints.insert(13);
    ints.insert(1);
    ints.insert(4);

    std::cout << "Int set after insertion: " << std::endl;
    for(std::set<int>::const_iterator it = ints.begin(); it != ints.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    //Insert some chars into a set.
    std::set<char> chars;

    chars.insert('b');
    chars.insert('2');
    chars.insert('w');
    chars.insert('!');
    chars.insert('a');

    std::cout << "Char set after insertion: " << std::endl;
    for(std::set<char>::const_iterator it = chars.begin(); it != chars.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    //Insert some Sortable objects into a set.
    std::set<Sortable> sorts;

    sorts.insert(Sortable(3));
    sorts.insert(Sortable(13));
    sorts.insert(Sortable(1));
    sorts.insert(Sortable(4));

    std::cout << "Sortable set after insertion: " << std::endl;
    for(std::set<Sortable>::const_iterator it = sorts.begin(); it != sorts.end(); ++it)
    {
        std::cout << it->mId << std::endl;
    }
}

void sortedVector()
{
}

void compareSetAndSortedVector()
{
}