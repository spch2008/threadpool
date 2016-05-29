/**
* @file   thread_pool.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-16 00:44:45
* @brief
**/

#include "thread_pool.h"
#include <memory>

ThreadPool::ThreadPool()
{
    _is_alive = true;
}

ThreadPool::~ThreadPool()
{
    ClearWork();
    ClearTask();
}

void ThreadPool::ClearWork()
{
    for (size_t i = 0; i < _work_threads.size(); i++)
    {
        delete _work_threads[i];
    }

    _work_threads.clear();
}

void ThreadPool::ClearTask()
{
    while(!_task_list.Empty())
    {
        Task *task = NULL;
        _task_list.Pop(&task);

        delete task;
    }
}

void ThreadPool::Init(int thread_num)
{
    for (int i = 0; i < thread_num; i++)
    {
        WorkerThread *worker = new WorkerThread(this);
        _work_threads.push_back(worker);
    }
}

void ThreadPool::Run()
{
    for (size_t i = 0; i < _work_threads.size(); i++)
    {
        WorkerThread *worker = _work_threads[i];
        worker->Run();
    }
}

void ThreadPool::Stop()
{
    _is_alive = false;

    for (size_t i = 0; i < _work_threads.size(); i++)
    {
        WorkerThread *worker = _work_threads[i];
        
        if (worker->IsAlive())
        {
            worker->Stop();
            worker->GetThreadControl().Join();
        }
    }

    ClearTask();
    ClearWork();
}

void ThreadPool::Exit(WorkerThread *worker)
{
    /* do some thread end op */
}

bool ThreadPool::AddTask(Task *task)
{
    if (_is_alive)
    {
        _task_list.Push(task);
        return true;
    }
    else
    {
        return false;
    }
}

Task *ThreadPool::GetTask(WorkerThread *worker)
{
    Task *task = NULL;
    _task_list.Pop(&task);

    if (task != NULL)
    {
        ThreadLocker::Locker sync(&_thread_locker);
        _busy_threads.insert(worker);
    }

    return task;
}

void ThreadPool::Idle(WorkerThread *worker)
{
    ThreadLocker::Locker sync(&_thread_locker);
    _busy_threads.erase(worker);
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
        if (_busy_threads.empty() && _task_list.Empty())
        {
            break;
        }
        else
        {
            _thread_locker.TimedWait(1000);
        }
    }

    /* stop all thread */
    Stop();
}

void ThreadPool::WorkerThread::Handler()
{
    while (!_finished)
    {
        Task *task = _thread_pool->GetTask(this);
        if (task != NULL)
        {
            auto_ptr<Task> at_task(task);

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
    _finished    = false;
}

ThreadPool::WorkerThread::~WorkerThread()
{
}

void ThreadPool::WorkerThread::Stop()
{
    _finished = true;
    _thread_pool->Notify();
}
