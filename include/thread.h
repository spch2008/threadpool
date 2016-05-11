/**
* @file   thread.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-11 19:27:52
* @brief
**/

#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

class Thread
{
public:
    Thread();
    virtual ~Thread();

    bool Start();
    void Stop();
    virtual void Handler() = 0;

protected:
    void Wait();
    static void *CallBack(void *thread);

private:
    Thread(const Thread &);
    Thread &operator=(const Thread &);

private:
    pthread_t _tid;
};

#endif
