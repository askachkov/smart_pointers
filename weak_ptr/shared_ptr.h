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

namespace _private_smart_ptr
{

struct IntRef
{
    int * mRef;
    operator int()const
    {
        if ( mRef != NULL )
            return *mRef;
        return 0;
    }

    int operator++()
    {
        if ( mRef != NULL )
            return ++(*mRef);
        return 0;
    }

    int operator--()
    {
        if ( mRef != NULL )
            return --(*mRef);
        return 0;
    }

    void free()
    {
        if ( mRef != NULL ){
            delete mRef;
            mRef = 0;
        }
    }
};

template<class T>
struct PImpl
{
    typedef std::function<void(T*)> Deleter;

    T ** pptr;
    Deleter deleter;
    IntRef refCounter;
    IntRef weakRefCounter;

    void clean()
    {
        refCounter.free();
        weakRefCounter.free();
        delete pptr;
        pptr = 0;
    }

    bool isEmpty()const
    {
        return pptr == NULL || *pptr == NULL;
    }

    void reset()
    {
        if ( !isEmpty() ){
            deleter(*pptr);
            *pptr = 0;
        }
    }
};

}

template<typename T>
class SharedPtr
{
private:
    _private_smart_ptr::PImpl<T> m_Impl;

public:

    SharedPtr(const _private_smart_ptr::PImpl<T> & pimpl):
        m_Impl(pimpl)
    {
        ++m_Impl.refCounter;
    }

    SharedPtr():
        m_Impl({NULL, std::bind(SingleDtor<T>(), std::placeholders::_1), {NULL}, {NULL}})
    {
    }

    SharedPtr(T * ptr, const typename _private_smart_ptr::PImpl<T>::Deleter & dtor = std::bind(SingleDtor<T>(), std::placeholders::_1) ):
        m_Impl({new T*(ptr), dtor, {new int(1)}, {new int(0)}})
    {
    }

    SharedPtr(const SharedPtr & o):
        m_Impl(o.m_Impl)
    {
        ++m_Impl.refCounter;
    }

    SharedPtr& operator=(const SharedPtr & o)
    {
        tryFree();
        m_Impl = o.m_Impl;
        ++m_Impl.refCounter;
        return *this;
    }

    ~SharedPtr()
    {
        tryFree();
    }

    T* operator->()
    {
        return *m_Impl.pptr;
    }

    T& operator*()
    {
        return **m_Impl.pptr;
    }

    T* get()
    {
        return *m_Impl.pptr;
    }

    int use_count()const
    {
        return m_Impl.refCounter;
    }

    void reset()
    {
        tryFree();
        m_Impl = {NULL, std::bind(SingleDtor<T>(), std::placeholders::_1), {NULL}, {NULL}};
    }

    _private_smart_ptr::PImpl<T> _getPrivateImpl()const
    {
        return m_Impl;
    }

private:
    void tryFree()
    {
        if ( !m_Impl.isEmpty() && --m_Impl.refCounter == 0 ){
            m_Impl.reset();
            if ( m_Impl.weakRefCounter == 0 ){
                m_Impl.clean();
            }
        }
    }
};

#endif // SHARED_PTR

