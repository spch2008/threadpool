/**
* @file   test_pool.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-21 09:48:32
* @brief
**/

#include "task.h"
#include "thread_pool.h"

#include <vector>
#include <unistd.h>
#include <iostream>
using namespace std;

class LogTask : public Task
{
public:
    void Exec()
    {
        write(0, "Log Done!\n", 10);
        sleep(1);
    }
};

int main()
{
    size_t log_cnt = 80;

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
