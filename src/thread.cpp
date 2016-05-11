/**
* @file   thread.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-11 19:33:44
* @brief
**/

#include "thread.h"
#include <unistd.h>
#include <iostream>
using namespace std;

Thread::Thread()
{
    _tid = -1;
}

Thread::~Thread()
{
    Stop();
    Wait();
}

bool Thread::Start()
{
    _tid = pthread_create(&_tid, NULL, Thread::CallBack, this);

    return _tid == 0;
}

void Thread::Stop()
{
    pthread_exit(NULL);
}

void *Thread::CallBack(void *arg)
{
    if (arg != NULL)
    {
        Thread *thread = reinterpret_cast<Thread*>(arg);
        thread->Handler();
    }

    return NULL;
}

void Thread::Wait()
{
    pthread_join(_tid, NULL);
}
