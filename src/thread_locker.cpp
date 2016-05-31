/**
* @file   thread_locker.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-14 14:40:26
* @brief
**/

#include "thread_locker.h"

ThreadLocker::ThreadLocker()
{
}

ThreadLocker::~ThreadLocker()
{
}

void ThreadLocker::Lock()
{
    _thread_mutex.Lock();
}

void ThreadLocker::UnLock()
{
    _thread_mutex.UnLock();
    _thread_cond.Signal();
}

bool ThreadLocker::TryLock()
{
    return _thread_mutex.TryLock();
}

void ThreadLocker::Wait()
{
    _thread_cond.Wait(&_thread_mutex);
}

bool ThreadLocker::TimedWait(int millisecond)
{
    return _thread_cond.TimedWait(millisecond, &_thread_mutex);
}

void ThreadLocker::Signal()
{
    _thread_cond.Signal();
}

void ThreadLocker::BroadCast()
{
    _thread_cond.BroadCast();
}
