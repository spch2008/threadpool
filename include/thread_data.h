/**
* @file   thread_data.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-06-17 09:50:18
* @brief
**/

#ifndef _THREAD_DATA_H_
#define _THREAD_DATA_H_

#include <pthread.h>
#include "exception.h"

class ThreadDataException : public Exception
{
public:
    ThreadDataException(const string &err) : Exception(err) {}
    ThreadDataException(const string &err, int code) : Exception(err, code) {}
    ~ThreadDataException() throw() {}
};

class ThreadDataManager
{
public:
    typedef pthread_key_t ThreadDataKey;

    class ThreadData
    {
    public:
        ThreadData() {}
        virtual ~ThreadData() {}
    };
    
    ThreadDataManager();
    ~ThreadDataManager();

    void SetData(ThreadData *data);
    void SetData(ThreadDataKey key, ThreadData *data);

    ThreadData *GetData();
    ThreadData *GetData(ThreadDataKey key);

protected:
    ThreadDataManager(const ThreadDataManager &);
    ThreadDataManager &operator=(const ThreadDataManager &);

    static void InitKey();
    static void DelKey(void *);

private:
    static pthread_once_t gOnceControl;
};

#endif
