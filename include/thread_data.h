/**
* @file   thread_data.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-06-17 09:50:18
* @brief
**/

#ifndef _THREAD_DATA_H_
#define _THREAD_DATA_H_

class ThreadData
{
public:
    ThreadData();
    ~ThreadData();

    void SetData(void *);
    void GetData();

    

private:
    ThredData(const ThreadData &);
    ThreadData &operator=(const ThreadData &);

};

#endif
