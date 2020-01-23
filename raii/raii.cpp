#include "raii.h"
#include <exception>
#include <iostream>
#include <string>

RAII::RAII(int bufSize):
    m_Res1(new Item[bufSize])
{
    std::cout << "RAII Ctor" << std::endl;
}

RAII::~RAII()
{
    delete[] m_Res1;
    std::cout << "RAII Dtor" << std::endl;
}

int RAII::manageRes2()
{
    try {
        Item * res2 = new Item[1];
        bool conditions[3] = {false, false, false};

        if ( conditions[0] ){
            delete[] res2;  // Problem 1
            std::cout << "Res 2 releazed in cond[0]!" << std::endl;
            return 0;
        }

        if ( conditions[1] ){
            delete[] res2;  // Problem 1
            std::cout << "Res 2 releazed in cond[1]!" << std::endl;
            return 0;
        }

        if ( conditions[2] ){
            delete[] res2;  // Problem 1
            std::cout << "Res 2 releazed in cond[2]!" << std::endl;
            return 0;
        }

        throuable();        // Problem 2
        delete[] res2;
        return 1;
    } catch (std::exception & e){
        std::cout << "Exc: " << e.what() << "; Memory leak for res2" << std::endl;
    }
    return -1;
}

void RAII::throuable()
{
    throw std::exception();
}
