/**
* @file   thread_locker.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-14 14:40:26
* @brief
**/

#include "thread_locker.h"

ThreadLocker::ThreadLocker()
{
    _notify_num = 0;
}

ThreadLocker::~ThreadLocker()
{
}

void ThreadLocker::Notify()
{
    if (_notify_num != -1)
    {
        _notify_num += 1;
    }
}

void ThreadLocker::NotifyAll()
{
    _notify_num = -1;
}

void ThreadLocker::Lock()
{
    _thread_mutex.Lock();
    _notify_num = 0;
}

void ThreadLocker::UnLock()
{
    _thread_mutex.UnLock();
    NotifyImpl();
}

bool ThreadLocker::TryLock()
{
    if (_thread_mutex.TryLock())
    {
        _notify_num = 0;
        return true;
    }
    else
    {
        return false;
    }
}

void ThreadLocker::Wait()
{
    NotifyImpl();

    _thread_cond.Wait(&_thread_mutex);
    _notify_num = 0;
}

bool ThreadLocker::TimedWait(int millisecond)
{
    NotifyImpl();

    if (_thread_cond.TimedWait(millisecond, &_thread_mutex))
    {
        _notify_num = 0;
        return true;
    }
    else
    {
        return false;
    }
}

void ThreadLocker::NotifyImpl()
{
    if (_notify_num != 0)
    {
        if (_notify_num == -1)
        {
            BroadCast();
        }
        else
        {
            for (int i = 0; i < _notify_num; i++)
            {
                Signal();
            }
        }

        _notify_num = 0;
    }
}

void ThreadLocker::Signal()
{
    _thread_cond.Signal();
}

void ThreadLocker::BroadCast()
{
    _thread_cond.BroadCast();
}
