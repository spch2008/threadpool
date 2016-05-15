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

using std::set;
using std::vector;

class ThreadPool
{
public:
    ThreadPool();
    ~ThreadPool();

    void Init(int thread_num);
    void Stop();

protected:
    class WorkerThread : public Thread
    {
    public:
        WorkerThread();
        ~WorkerThread();

        void Handler();

    private:
        ThreadPool *_thread_pool;
    };

private:
    set<WorkerThread*>    _busy_queues;
    vector<WorkerThread*> _job_queues; 

    ThreadQueue<Task*> _job_list;
};

#endif
