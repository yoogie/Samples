#include <vector>
#include "Foo.h"

using namespace std;

void freeVectorMemory()
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
    foos.reserve(100);

    //insert some data into the vector
    Foo dummyData;
    for(int ii = 0; ii < 100; ++ii)
    {
        foos.push_back(dummyData);        
    }
    cout << "Done making copies of dummy obj into the map" << endl << endl;

    foos.erase(foos.begin()+10, foos.end());
    cout << "Done removing elements at the end of the vector" << endl << endl;

    vector<Foo>(foos).swap(foos);
    //All the elements left in the vector are copied to the new vector.
}
