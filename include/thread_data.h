/**
* @file   thread_data.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-06-17 09:50:18
* @brief
**/

#ifndef _THREAD_DATA_H_
#define _THREAD_DATA_H_

#include <pthread.h>

class ThreadData
{
public:
    ThreadData() {}
    virtual ~ThreadData() {}
};

class ThreadDataManager
{
public:
    typedef pthread_key_t ThreadDataKey;
    
    ThreadDataManager();
    ~ThreadDataManager();

    void SetData(ThreadData *data);
    void SetData(ThreadDataKey key, ThreadData *data);

    ThreadData *GetData();
    ThreadData *GetData(ThreadDataKey key);

private:
    ThreadDataManager(const ThreadDataManager &);
    ThreadDataManager &operator=(const ThreadDataManager &);

private:
    static pthread_key_t gThreadKey;
};

#endif
