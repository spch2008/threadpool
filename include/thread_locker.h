/**
* @file   thread_locker.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-14 14:40:26
* @brief
**/

#ifndef _THREAD_LOCKER_H_
#define _THREAD_LOCKER_H_

#include "thread_mutex.h"
#include "thread_cond.h"

template <typename T>
class LockerManager
{
public:
    LockerManager(T *locker) : _locker(locker)
    {
        _locker->Lock();
    }

    ~LockerManager()
    {
        _locker->UnLock();
    }

protected:
    LockerManager(const LockerManager &);
    LockerManager &operator=(const LockerManager &);

private:
    T *_locker;

};

class ThreadLocker
{
public:
    ThreadLocker();
    ~ThreadLocker();

    void Lock();
    void UnLock();
    bool TryLock();

    void Signal();
    void BroadCast();

    void Wait();
    bool TimedWait(int millisecond);

    typedef LockerManager<ThreadLocker> Locker;

protected:
    ThreadLocker(const ThreadLocker &);
    ThreadLocker &operator=(const ThreadLocker &);

private:
    ThreadMutex _thread_mutex;
    ThreadCond  _thread_cond;
};

#endif
