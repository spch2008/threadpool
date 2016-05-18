/**
* @file   thread_pool.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-16 00:44:45
* @brief
**/

#include "thread_pool.h"

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
    for (size_t i = 0; i < _job_queues.size(); i++)
    {
        delete _job_queues[i];
    }

    _job_queues.clear();
}

void ThreadPool::Init(int thread_num)
{
    for (int i = 0; i < thread_num; i++)
    {
        WorkerThread *worker = new WorkerThread(this);
        _job_queues.push_back(worker);
    }
}

void ThreadPool::Run()
{
    for (size_t i = 0; i < _job_queues.size(); i++)
    {
        WorkerThread *worker = _job_queues[i];
        worker->Run();
    }
}

void ThreadPool::Stop()
{
    for (size_t i = 0; i < _job_queues.size(); i++)
    {
        WorkerThread *worker = _job_queues[i];
        
        if (worker->IsAlive())
        {
            worker->GetThreadControl().Stop();
            worker->GetThreadControl().Join();
        }
    }
}

void ThreadPool::Exit(WorkerThread *worker)
{
    for (vector<WorkerThread*>::iterator iter = _job_queues.begin();
         iter != _job_queues.end();
         iter ++)
    {
        if (*iter == worker)
        {
            delete worker;
            _job_queues.erase(iter);
            break;
        }
    }
}

void ThreadPool::AddTask(Task *task)
{
    _task_list.Push(task);
}

Task *ThreadPool::GetTask(WorkerThread *worker)
{
    Task *task = NULL;
    _task_list.Pop(&task);

    if (task != NULL)
    {
        ThreadLocker::Locker sync(&_thread_locker);
        _busy_queues.insert(worker);
    }

    return task;
}

void ThreadPool::Idle(WorkerThread *worker)
{
    ThreadLocker::Locker sync(&_thread_locker);
    _busy_queues.erase(worker);
}

void ThreadPool::Notify()
{
    _task_list.Notify();
}

void ThreadPool::WaitForAllDone()
{
    ThreadLocker::Locker sync(&_thread_locker);
    while (true)
    {
        if (_busy_queues.empty() && _job_queues.empty())
        {
            break;
        }
        else
        {
            _thread_locker.TimedWait(1000);
        }
    }
}

void ThreadPool::WorkerThread::Handler()
{
    while (!_end)
    {
        Task *task = _thread_pool->GetTask(this);
        if (task != NULL)
        {
            try
            {
                task->Exec();
            }
            catch(...)
            {
            }

            _thread_pool->Idle(this);
        }
    }

    _thread_pool->Exit(this);
}

ThreadPool::WorkerThread::WorkerThread(ThreadPool *thread_pool)
{
    _thread_pool = thread_pool;
    _end         = false;
}

ThreadPool::WorkerThread::~WorkerThread()
{
}

void ThreadPool::WorkerThread::Stop()
{
    _end = true;
    _thread_pool->Notify();
}
