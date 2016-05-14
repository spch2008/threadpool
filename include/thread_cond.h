/**
* @file   thread_cond.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-14 10:44:57
* @brief
**/

#ifndef _THREAD_COND_H_
#define _THREAD_COND_H_

#include <pthread.h>
#include "exception.h"

class CondException : public Exception
{
public:
    CondException(const string &text) : Exception(text) {}
    CondException(const string &text, int err) : Exception(text, err) {}
    ~CondException() throw() {}
};


class ThreadMutex;
class ThreadCond
{
public:
    ThreadCond();
    ~ThreadCond();

    void Signal();
    void BroadCast();

    void Wait(ThreadMutex *mutex);
    /* true: event come; false: time out */
    bool TimedWait(int millisecond, ThreadMutex *mutex);

protected:
    typedef struct timespec TimeSpec;
    void GetAbsTime(int millisecond, TimeSpec *time_spec);

private:
    ThreadCond(const ThreadCond &);
    ThreadCond &operator=(const ThreadCond &);

private:
    pthread_cond_t _cond;
};

#endif
