#ifndef RAII_H
#define RAII_H

#include "uniq_ptr.h"
#include <memory>
#include "item.h"

//RAII (Resource acquisition is initialization)
class RAII
{
    //typedef UniqPtr<Item, ArrayDtor<Item> > BufferPtr;
    typedef std::unique_ptr<Item, ArrayDtor<Item> > BufferPtr;

public:
    explicit RAII(int bufSize);
    ~RAII();
    int manageRes2();

private:
    void throuable();

private:
    BufferPtr m_Res1;
};

#endif // RAII_H
