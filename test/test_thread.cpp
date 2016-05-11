/**
* @file   main.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-11 19:57:31
* @brief
**/

#include "thread.h"
#include <unistd.h>

#include <memory>
#include <iostream>
using namespace std;

class TestThread : public Thread
{
public:
    void Handler()
    {
        cout << "I am a thread!" << endl;
    }
};

int main()
{
    auto_ptr<Thread> thread(new TestThread);
    Thread *th = thread.get();

    th->Start();
    sleep(2);    

    return 0;
}
