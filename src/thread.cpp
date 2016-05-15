/**
* @file   thread.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-11 19:33:44
* @brief
**/

#include "thread.h"
#include <unistd.h>
#include <errno.h>
#include <iostream>
using namespace std;

Thread::Thread()
{
    _tid = -1;
    _is_alive = false;
}

Thread::~Thread()
{
    Stop();
}

void Thread::Start()
{
    if (_is_alive)
    {
        throw ThreadException("Thread::Start Already Running!");
    }

    _tid = pthread_create(&_tid, NULL, Thread::CallBack, this);
    if (_tid != 0)
    {
        throw ThreadException("Thread::Start", _tid);
    }
}

void *Thread::CallBack(void *arg)
{
    Thread *thread = reinterpret_cast<Thread*>(arg);
    thread->_is_alive = true;

    try
    {
        thread->Handler();
    }
    catch(...)
    {
        thread->_is_alive = false;
        throw;
    }

    thread->_is_alive = false;
    return NULL;
}

void Thread::Wait()
{
    int ret = pthread_join(_tid, NULL);
    if (ret != ESRCH)
    {
        throw ThreadException("Thread::Wait", ret);
    }
}

void Thread::Stop()
{
    if (_is_alive)
    {
        _is_alive = false;
        pthread_exit(NULL);
    }

    Wait();
}

bool Thread::IsAlive() const
{
    return _is_alive;
}
