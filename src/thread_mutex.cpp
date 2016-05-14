/**
* @file   thread_mutex.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-13 10:13:13
* @brief
**/

#include "thread_mutex.h"

ThreadMutex::ThreadMutex()
{
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_ERRORCHECK);

    pthread_mutex_init(&_mutex, &mutex_attr);
    pthread_mutexattr_destroy(&mutex_attr);
}

ThreadMutex::~ThreadMutex()
{
    pthread_mutex_destroy(&_mutex);
}

void ThreadMutex::Lock()
{
    int ret = pthread_mutex_lock(&_mutex);
    if (ret != 0)
    {
        throw MutexException("ThreadMutex::Lock", ret);
    }
}

void ThreadMutex::UnLock()
{
    int ret = pthread_mutex_unlock(&_mutex);
    if (ret != 0)
    {
        throw MutexException("ThreadMutex::UnLock", ret);
    }
}

bool ThreadMutex::TryLock()
{
    int ret = pthread_mutex_trylock(&_mutex);
    if (ret == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
