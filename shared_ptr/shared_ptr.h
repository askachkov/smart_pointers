#ifndef SHARED_PTR
#define SHARED_PTR

#include <functional>

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

template<typename T>
class SharedPtr
{
public:
    typedef std::function<void(T*)> Deleter;
private:

    T * m_Ptr;
    Deleter m_Deleter;
    union {
        int & m_RefCounter;
        int * m_pRefCounter;
    };

public:
    SharedPtr(T * ptr = 0, const Deleter & dtor = std::bind(SingleDtor<T>(), std::placeholders::_1) ):
        m_Ptr(ptr),
        m_pRefCounter(new int(1)),
        m_Deleter(dtor)
    {
    }

    SharedPtr(const SharedPtr & o):
        m_Ptr(o.m_Ptr),
        m_pRefCounter(o.m_pRefCounter)
    {
        m_RefCounter++;
    }

    SharedPtr& operator=(const SharedPtr & o)
    {
        tryFree();
        m_Ptr = o.m_Ptr;
        m_pRefCounter = o.m_pRefCounter;
        m_RefCounter++;
        return *this;
    }

    ~SharedPtr()
    {
        tryFree();
    }

    T* operator->()
    {
        return m_Ptr;
    }

    T& operator*()
    {
        return *m_Ptr;
    }

    T* get()
    {
        return m_Ptr;
    }

    int use_count()const
    {
        return m_RefCounter;
    }

private:
    void tryFree()
    {
        if ( m_Ptr && --m_RefCounter == 0 ){
            delete m_pRefCounter;
            m_pRefCounter = 0;
            m_Deleter(m_Ptr);
            m_Ptr = 0;
        }
    }
};

#endif // SHARED_PTR

