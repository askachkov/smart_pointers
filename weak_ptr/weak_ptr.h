#ifndef WEAK_PTR
#define WEAK_PTR

#include "shared_ptr.h"

template<typename T>
class WeakPtr
{
    _private_smart_ptr::PImpl<T> m_Impl;
public:

    WeakPtr():
        m_Impl({NULL, _private_smart_ptr::PImpl<T>::Deleter(), NULL, NULL})
    {

    }

    WeakPtr(const SharedPtr<T> & o):
        m_Impl(o._getPrivateImpl())
    {
        ++m_Impl.weakRefCounter;
    }

    WeakPtr(const WeakPtr & o):
        m_Impl(o.m_Impl)
    {
        ++m_Impl.weakRefCounter;
    }

    WeakPtr& operator=(const WeakPtr & o)
    {
        tryFree();
        m_Impl = o.m_Impl;
        ++m_Impl.weakRefCounter;
        return *this;
    }

    ~WeakPtr()
    {
        tryFree();
    }

    int use_count()const
    {
        return m_Impl.refCounter;
    }

    SharedPtr<T> lock()const
    {
        SharedPtr<T> res(m_Impl);
        return res;
    }

    bool expired()const
    {
        return m_Impl.isEmpty();
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
        if ( m_Impl.pptr && --m_Impl.weakRefCounter == 0 && m_Impl.refCounter == 0 ){
            m_Impl.clean();
        }
    }
};

#endif // WEAK_PTR

