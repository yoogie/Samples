#ifndef LOCKEDPTR_H
#define LOCKEDPTR_H

#include <windows.h> //TODO Rewrite using some platform independent lock instead if windows CRITICAL_SECTION

template <typename T>
class LockedPtr
{
public:
    //Lock the critical section and remove volatile atrib from obj
    explicit LockedPtr(CRITICAL_SECTION& criticalSection, volatile T& obj) 
        : m_criticalSection(criticalSection) 
        , m_obj(const_cast<T*>(&obj))
    {
        EnterCriticalSection(&m_criticalSection);
    }

    //Unlock the critical section.
    ~LockedPtr() 
    {
        LeaveCriticalSection(&m_criticalSection);
    }

    T& operator*() 
    {
        return *m_obj;
    }

    T* operator->()
    {
        return m_obj;
    }

private:
    LockedPtr();
    LockedPtr(const LockedPtr& arg);
    LockedPtr& operator=(const LockedPtr& arg);

    CRITICAL_SECTION& m_criticalSection;
    T* m_obj;
};

#endif