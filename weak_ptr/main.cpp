#include <iostream>

#include "item.h"
#include "shared_ptr.h"
#include "weak_ptr.h"
#include <memory>

namespace std
{
    typedef std::weak_ptr<Item> WeakItem;
    typedef std::shared_ptr<Item> SharedItem;
}

namespace custom
{
    typedef WeakPtr<Item> WeakItem;
    typedef SharedPtr<Item> SharedItem;
}

using namespace std;

SharedItem createSharedPointer()
{
    SharedItem empty;
    WeakItem emptyWeak;
    emptyWeak = empty;
    SharedItem item( new Item );
    empty = item;
    std::cout << "1. Refs: " << item.use_count() << std::endl;
    empty.reset();
    std::cout << "2. Refs: " << item.use_count() << std::endl;
    emptyWeak.reset();
    return item;
}

void checkSharedPointer(const SharedItem & item)
{
    std::cout << "4. Refs: " << item.use_count() << std::endl;
}

void checkWeakPointer(const WeakItem & item)
{
    std::cout << "3. Expired: " << (item.expired() ? "true" : "false") << std::endl;
    checkSharedPointer(item.lock());
}

int main()
{
    checkWeakPointer(createSharedPointer());
    return 0;
}

