#include <algorithm>
#include <vector>
#include <list>
#include <iostream>

#include "mapUsage.h"
#include "benchmark_basic.h"
#include "VectorUsage.h"
#include "SortedData.h"

int main()
{
    //Map usage
    useMap(); std::cout << std::endl;
    useMapInDepth(); std::cout << std::endl;
    mapInsertOrOverwrite(); std::cout << std::endl;
    useSmartpointersInMaps(); std::cout << std::endl;

    //A little about multimaps
    findInMultiMap(); std::cout << std::endl;

    //Removing elements and freeing memory
    removeFromMap(); std::cout << std::endl;
    freeVectorMemory(); std::cout << std::endl;

    //Itterators
    itterate(); std::cout << std::endl;

    //Some basic benchmarks
    benchmarkInsert(); std::cout << std::endl;
    benchmarkLookup(); std::cout << std::endl;
    benchmarkDelete(); std::cout << std::endl;

    //Sorted data
    useASet(); std::cout << std::endl;
    sortedVector(); std::cout << std::endl;
    compareSetAndSortedVector(); std::cout << std::endl;

    return 1;
}
