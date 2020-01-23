#include <iostream>
#include "raii.h"

using namespace std;

void testRAII()
{
    RAII handler(3);
    handler.manageRes2();
}

/**
 * @brief main - check RAII (Resource acquisition is initialization)
 *               with big functions with many exit points we have a risk for memory leaks.
 *
 * @return
 */

int main()
{
    cout << "Part 1 - RAII (Resource acquisition is initialization)" << endl << endl;
    testRAII();
    return 0;
}

