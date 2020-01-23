#ifndef POINTER_H
#define POINTER_H

template<typename T>
struct SingleDtor
{
    void operator()(T * o)
    {
        delete o;
    }
};

template<typename T>
struct ArrayDtor
{
    void operator()(T * o)
    {
        delete[] o;
    }
};

template<typename T, typename Dtor = SingleDtor<T> >
class UniqPtr
{
public:
    UniqPtr(const UniqPtr &) = delete;
    void operator=(const UniqPtr &) = delete;

public:
    UniqPtr(T * res):
        m_Resource(res)
    {
    }

    ~UniqPtr()
    {
        Dtor _d;
        _d(m_Resource);
    }

    T & operator*()
    {
        return *m_Resource;
    }

    T* operator->()
    {
        return m_Resource;
    }

private:
    T * m_Resource;
};

#endif // POINTER_H
