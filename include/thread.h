/**
* @file   thread.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-11 19:27:52
* @brief
**/

#ifndef _THREAD_H_
#define _THREAD_H_

#include <string>
#include <pthread.h>
#include "exception.h"

using std::string;

class ThreadException : public Exception
{
public:
    ThreadException(const string &err) : Exception(err) {}
    ThreadException(const string &err, int code) : Exception(err, code) {}
    ~ThreadException() throw() {}
};

class ThreadControl
{
public:
    explicit ThreadControl(pthread_t tid);
    ~ThreadControl();

    void Join();
    void Stop();
    void Detach();
    pthread_t Id();

private:
    pthread_t _tid;
};

class Thread
{
public:
    Thread();
    virtual ~Thread();

    ThreadControl Run();
    ThreadControl GetThreadControl();

    bool IsAlive() const;
    virtual void Handler() = 0;

protected:
    static void *CallBack(void *thread);

private:
    Thread(const Thread &);
    Thread &operator=(const Thread &);

private:
    pthread_t _tid;
    bool      _is_alive;
};

#endif
