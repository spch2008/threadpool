/**
* @file   thread_mutex.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-13 10:13:21
* @brief
**/

#ifndef _THREAD_MUTEX_H_
#define _THREAD_MUTEX_H_

#include <pthread.h>
#include "exception.h"

class MutexException : public Exception
{
public:
    MutexException(const string &err) : Exception(err) {}
    MutexException(const string &err, int code) : Exception(err, code) {}
    virtual ~MutexException() throw() {}
};

class ThreadMutex
{
public:
    ThreadMutex();
    ~ThreadMutex();

    void Lock();
    void UnLock();
    bool TryLock();

private:
    pthread_mutex_t _mutex;
};

#endif
