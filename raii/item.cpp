#include "item.h"
#include <iostream>

Item::Item()
{
    debug("DefaultCtor");
}

Item::Item(const Item &)
{
    debug("CopyCtor");
}

Item::~Item()
{
    debug("Dtor");
}

Item &Item::operator=(const Item &)
{
    debug("OperatorCopy");
    return *this;
}

void Item::debug(const char *str)
{
    using namespace std;
    cout << "[Item:" << str << "]" << endl;
}

