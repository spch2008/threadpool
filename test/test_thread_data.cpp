/**
* @file   test_thread_data.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-21 09:48:32
* @brief
**/

#include <unistd.h>

#include <vector>
#include <iostream>

#include "task.h"
#include "thread_pool.h"
#include "thread_data.h"

using std::cout;
using std::endl;

ThreadDataManager gDataManager;

class LocalData : public ThreadDataManager::ThreadData
{
public:
    LocalData()
    {
        cout << pthread_self() << " create local data" << endl;
    }

    ~LocalData()
    {
        cout << pthread_self() << " delete local data" << endl;
    }

    void Print()
    {
        cout << pthread_self() << " success" << endl;
    }
};

class LogTask : public Task
{
public:
    void Exec()
    {
        ThreadDataManager::ThreadData *local_data = new LocalData;
        gDataManager.SetData(local_data);

        write(0, "Task Done!\n", 10);
        sleep(1);

        local_data = gDataManager.GetData();
        LocalData *td = dynamic_cast<LocalData*>(local_data);
        if (local_data == NULL)
        {
            cout << "return empty" << endl;
        }
        else
        {
            td->Print();
        }

        gDataManager.DelData();
    }
};

int main()
{
    size_t log_cnt = 3;

    vector<Task*> log_tasks;
    for (size_t i = 0; i < log_cnt; i++)
    {
        Task *task = new LogTask;
        log_tasks.push_back(task);
    }

    ThreadPool thread_pool;
    thread_pool.Init(10);

    for (size_t i = 0; i < log_cnt; i++)
    {
        thread_pool.AddTask(log_tasks[i]);
    }

    thread_pool.Run();
    thread_pool.WaitForAllDone();

    return 0;
}
