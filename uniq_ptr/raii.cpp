#include "raii.h"
#include <exception>
#include <iostream>

RAII::RAII(int bufSize):
    m_Res1(new Item[bufSize])
{
    std::cout << "RAII Ctor" << std::endl;
}

RAII::~RAII()
{
    std::cout << "RAII Dtor" << std::endl;
}

int RAII::manageRes2()
{
    try {
        BufferPtr res2(new Item[1]);
        bool conditions[3] = {false, false, false};

        if ( conditions[0] ){
            return 0;
        }

        if ( conditions[1] ){
            return 0;
        }

        if ( conditions[2] ){
            return 0;
        }

        throuable();
        return 1;
    } catch (std::exception & e){
        std::cout << "Exc: " << e.what() << "; No memory leak for res2" << std::endl;
    }
    return -1;
}

void RAII::throuable()
{
    throw std::exception();
}
