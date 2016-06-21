/**
* @file   thread_data.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-06-17 09:50:18
* @brief
**/

#include "thread_data.h"

pthread_key_t gThreadKey;
pthread_once_t ThreadDataManager::gOnceControl = PTHREAD_ONCE_INIT;

ThreadDataManager::ThreadDataManager()
{
    pthread_once(&gOnceControl, &ThreadDataManager::InitKey);
}

ThreadDataManager::~ThreadDataManager()
{
}

void ThreadDataManager::InitKey()
{
    int ret = pthread_key_create(&gThreadKey, &DelKey);
    if (ret != 0)
    {
        throw ThreadDataException("ThreadDataManager::InitKey", ret);
    }
}

void ThreadDataManager::DelKey(void *)
{
    int ret = pthread_key_delete(gThreadKey);
    if (ret != 0)
    {
        throw ThreadDataException("ThreadDataManager::DelKey", ret);
    }
}

void ThreadDataManager::SetData(ThreadData *data)
{
    ThreadData *old_data = GetData();
    if (old_data != NULL)
    {
        delete old_data;
    }

    int ret = pthread_setspecific(gThreadKey, data);
    if (ret != 0)
    {
        throw ThreadDataException("ThreadDataManager::SetData", ret);
    }
}

void ThreadDataManager::SetData(ThreadDataKey key, ThreadData  *data)
{
    ThreadData *old_data = GetData(key);
    if (old_data != NULL)
    {
        delete old_data;
    }

    int ret = pthread_setspecific(key, data);
    if (ret != 0)
    {
        throw ThreadDataException("ThreadDataManager::SetData", ret);
    }
}

ThreadDataManager::ThreadData *ThreadDataManager::GetData()
{
    return static_cast<ThreadData*>(pthread_getspecific(gThreadKey));
}

ThreadDataManager::ThreadData *ThreadDataManager::GetData(ThreadDataKey key)
{
    return static_cast<ThreadData*>(pthread_getspecific(key));
}
