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

ThreadControl::ThreadControl(pthread_t tid)
{
    _tid = tid;
}

ThreadControl::~ThreadControl()
{
}

void ThreadControl::Join()
{
    if (pthread_self() == _tid)
    {
        throw ThreadException("ThreadControl::Join Same Thread");
    }

    int ret = pthread_join(_tid, NULL);
    if (ret != 0)
    {
        throw ThreadException("ThreadControl::Join", ret);
    }
}

void ThreadControl::Stop()
{
    if (pthread_self() == _tid)
    {
        throw ThreadException("ThreadControl::Join Same Thread");
    }

    int ret = pthread_cancel(_tid);
    if (ret != 0)
    {
        throw ThreadException("ThreadControl::Stop", ret);
    }
}

void ThreadControl::Detach()
{
    int ret = pthread_detach(_tid);
    if (ret != 0)
    {
        throw ThreadException("Thread::Detach", ret);
    }
}

pthread_t ThreadControl::Id()
{
    return _tid;
}

Thread::Thread()
{
    _tid = -1;
    _is_alive = false;
}

Thread::~Thread()
{
}

ThreadControl Thread::Run()
{
    if (_is_alive)
    {
        throw ThreadException("Thread::Start Already Running!");
    }

    int ret = pthread_create(&_tid, NULL, Thread::CallBack, this);
    if (ret != 0)
    {
        throw ThreadException("Thread::Start", ret);
    }

    return ThreadControl(_tid);
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

bool Thread::IsAlive() const
{
    return _is_alive;
}

ThreadControl Thread::GetThreadControl()
{
    return ThreadControl(_tid);
}
