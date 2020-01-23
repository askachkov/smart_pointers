#include <iostream>
#include "uniq_ptr.h"
#include "item.h"
#include "raii.h"

using namespace std;

void testSinglPtr()
{
    cout << "++++testSinglPtr:" << endl;
    UniqPtr<Item> ptr(new Item);
}

void testArrayPtr()
{
    cout << "++++testArrayPtr:" << endl;
    UniqPtr<Item, ArrayDtor<Item> > ptr(new Item[4]);
}

void testRAII()
{
    cout << "++++testRAII:" << endl;
    RAII handler(5);
    handler.manageRes2();
}

int main()
{
    testSinglPtr();
    testArrayPtr();
    testRAII();
    return 0;
}

