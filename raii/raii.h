#ifndef RAII_H
#define RAII_H

#include "item.h"

//RAII (Resource acquisition is initialization)
class RAII
{
public:
    explicit RAII(int bufSize);
    ~RAII();
    int manageRes2();

private:
    void throuable();

private:
    Item * m_Res1;
};

#endif // RAII_H
