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

class NonSortable
{
public:
    NonSortable(int id) : mId(id) {}
    int mId;
private:
    NonSortable();
};

bool comparefunction(const NonSortable& lhs, const NonSortable& rhs)
{
    return lhs.mId < rhs.mId;
}

typedef bool(*Comparator)(const NonSortable& lhs, const NonSortable& rhs);

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
    //It is not possible to insert objects that 
    //does not have  a operator< implemented.
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

    //Insert some NonSortable objects into a set
    //using a local sorter function
    //std::set<NonSortable, bool(*)(const NonSortable& lhs, const NonSortable& rhs)> nonSorts(&comparefunction);
    std::set<NonSortable, Comparator> nonSorts(&comparefunction);
    nonSorts.insert(NonSortable(3));
    nonSorts.insert(NonSortable(13));
    nonSorts.insert(NonSortable(1));
    nonSorts.insert(NonSortable(4));

    std::cout << "NonSortable set after insertion: " << std::endl;
    for(std::set<NonSortable, Comparator>::const_iterator it = nonSorts.begin(); it != nonSorts.end(); ++it)
    {
        std::cout << it->mId << std::endl;
    }

    //Insert some more ints into a set
    std::set<int> moreInts;
    moreInts.insert(3);
    moreInts.insert(13);
    moreInts.insert(1);
    moreInts.insert(4);
    moreInts.insert(4);
    moreInts.insert(4);
    moreInts.insert(4);

    //Since a set contains unique objects
    std::cout << "Int set after insertion: " << std::endl;
    for(std::set<int>::const_iterator it = ints.begin(); it != ints.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    
    std::pair<std::set<int>::iterator, bool> res = moreInts.insert(4);
    std::cout << "res.bool = " << res.second << " after trying to inser 4 for the 5th time." << std::endl;
}

void sortedVector()
{
    using std::sort;
    using std::unique;

    std::vector<int> ints;
    ints.push_back(3);
    ints.push_back(13);
    ints.push_back(1);
    ints.push_back(4);

    std::cout << "Int vector after insertion: " << std::endl;
    for(std::vector<int>::const_iterator it = ints.begin(); it != ints.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    sort(ints.begin(), ints.end());
    
    std::cout << "Int vector after sort: " << std::endl;
    for(std::vector<int>::const_iterator it = ints.begin(); it != ints.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    //Insert some more ints into a vector
    std::vector<int> moreInts;
    moreInts.push_back(3);
    moreInts.push_back(13);    
    moreInts.push_back(4);
    moreInts.push_back(1);
    moreInts.push_back(4);
    moreInts.push_back(4);
    moreInts.push_back(4);

    std::cout << "Int vector after insertion: " << std::endl;
    for(std::vector<int>::const_iterator it = moreInts.begin(); it != moreInts.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    //To have the vector similar to the set, sort and remove copies
    sort(moreInts.begin(), moreInts.end()); //sort before making unique since std::unique only checks elements next to each other
    std::vector<int>::iterator newEndIt = unique(moreInts.begin(), moreInts.end());
    
    std::cout << "Int vector after sorting and removing copies: " << std::endl;
    for(std::vector<int>::const_iterator it = moreInts.begin(); it != moreInts.end(); ++it)
    {
        std::cout << *it << std::endl;
    }

    //Since std::unique does not invalidate elements after the last unique element we need to manualy shrink the vector
    moreInts.resize(newEndIt - moreInts.begin());
    std::cout << "Int vector after resize: " << std::endl;
    for(std::vector<int>::const_iterator it = moreInts.begin(); it != moreInts.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

void compareSetAndSortedVector()
{
}