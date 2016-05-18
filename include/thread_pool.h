/**
* @file   thread_pool.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-16 00:44:45
* @brief
**/

#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <set>
#include <vector>

#include "task.h"
#include "thread.h"
#include "thread_queue.h"
#include "thread_locker.h"

using std::set;
using std::vector;

class PoolException : public Exception
{
public:
    PoolException(const string &err) : Exception(err) {}
    PoolException(const string &err, int code) : Exception(err, code) {}
    ~PoolException() throw() {}
};

class ThreadPool
{
public:
    ThreadPool();
    ~ThreadPool();
    
    void Run();
    void Stop();

    void WaitForAllDone();
    void AddTask(Task *task);
    void Init(int thread_num);

protected:
    class WorkerThread : public Thread
    {
    public:
        WorkerThread(ThreadPool *thread_pool);
        ~WorkerThread();

        void Stop();
    
    protected:
        void Handler();

    private:
        ThreadPool *_thread_pool;
        bool        _end;
    };

    Task *GetTask(WorkerThread *worker);
    void  Idle(WorkerThread *worker);
    void  Exit(WorkerThread *worker);
    void  Notify();

    friend class WorkerThread;

private:
    set<WorkerThread*>    _busy_queues;
    vector<WorkerThread*> _job_queues; 

    ThreadQueue<Task*> _task_list;
    ThreadLocker       _thread_locker;
};

#endif
