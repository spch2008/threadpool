/**
* @file   thread_mutex.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-13 10:13:21
* @brief
**/

#ifndef _THREAD_MUTEX_H_
#define _THREAD_MUTEX_H_

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
