/**
* @file   thread_cond.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-14 10:44:57
* @brief
**/

#include "thread_cond.h"
#include "thread_mutex.h"
#include <sys/time.h>
#include <errno.h>
#include <stdint.h>

ThreadCond::ThreadCond()
{
    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);

    pthread_cond_init(&_cond, &cond_attr);
    pthread_condattr_destroy(&cond_attr);
}

ThreadCond::~ThreadCond()
{
    pthread_cond_destroy(&_cond);
}

void ThreadCond::Signal()
{
    int ret = pthread_cond_signal(&_cond);
    if (ret != 0)
    {
        throw CondException("ThreadCond::Singal", ret);
    }
}

void ThreadCond::BroadCast()
{
    int ret = pthread_cond_broadcast(&_cond);
    if (ret != 0)
    {
        throw CondException("ThreadCond::BroadCast", ret);
    }
}

void ThreadCond::Wait(ThreadMutex *mutex)
{
    int ret = pthread_cond_wait(&_cond, &mutex->_mutex);
    if (ret != 0)
    {
        throw CondException("ThreadCond::Wait", ret);
    }
}

bool ThreadCond::TimedWait(int millisecond, ThreadMutex *mutex)
{
    TimeSpec time_spec;
    GetAbsTime(millisecond, &time_spec);

    int ret = pthread_cond_timedwait(&_cond, &mutex->_mutex, &time_spec);
    if (ret == 0)
    {
        return true;
    }
    else if (ret == ETIMEDOUT)
    {
        return false;
    }
    else
    {
        throw CondException("ThreadCond::TimedWait", ret);
    }
}

void ThreadCond::GetAbsTime(int millisecond, TimeSpec *time_spec)
{
    timeval time_val;
    gettimeofday(&time_val, NULL);

    int64_t usec = time_val.tv_sec * static_cast<int64_t>(1000000) +
                         millisecond * static_cast<int64_t>(1000) +
                         time_val.tv_usec;

    time_spec->tv_sec  =  usec / 1000000;
    time_spec->tv_nsec = (usec % 1000000) * 1000;
}
