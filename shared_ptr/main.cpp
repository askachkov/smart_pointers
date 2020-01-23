#include <iostream>
#include "shared_ptr.h"
#include "item.h"
#include <memory>

using namespace std;

//typedef SharedPtr<Item> SmartPtr;
typedef std::shared_ptr<Item> SmartPtr;

//typedef SharedPtr<Item> SmartArray;
typedef std::shared_ptr<Item> SmartArray;

void testSingle()
{
    cout << "++++Test single++++" << endl;
    bool condition = true;
    SmartPtr pItem(new Item);
    if ( condition ){
        SmartPtr b[10];
        for ( int i = 0; i < 10; ++i ){
            b[i] = pItem;
        }
        cout << "SharedPtr was copied - refs:" << pItem.use_count() << endl;
    }
}

void testArray()
{
    cout << "++++Test array++++" << endl;
    bool condition = true;
    SmartArray pItem(new Item[2], ArrayDtor<Item>());
    if ( condition ){
        SmartArray b[10];
        for ( int i = 0; i < 10; ++i ){
            b[i] = pItem;
        }
        cout << "SharedPtr was copied - refs:" << pItem.use_count() << endl;
    }
}

int main()
{
    testSingle();
    testArray();
    return 0;
}

struct BadItem: public enable_shared_from_this<BadItem>
{
    BadItem()
    {
        //bad_weak_ptr
        cout << shared_from_this() << endl;
    }
    ~BadItem()
    {

        cout << shared_from_this() << endl;
    }
};



