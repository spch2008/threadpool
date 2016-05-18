/**
* @file   thread_queue.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-15 22:09:34
* @brief
**/

#ifndef _THREAD_QUEUE_H_
#define _THREAD_QUEUE_H_

#include <list>
#include "thread_locker.h"
using std::list;

template <typename Item>
class ThreadQueue
{
public:
    ThreadQueue() {}
    ~ThreadQueue() {}

    void Push(const Item &item);
    bool Pop(Item *item);
    bool Empty() const;

protected:
    ThreadQueue(const ThreadQueue &);
    ThreadQueue &operator=(const ThreadQueue &);

private:
    list<Item>   _queue;
    ThreadLocker _locker;
};

template <typename Item>
void ThreadQueue<Item>::Push(const Item &item)
{
    ThreadLocker::Locker lock(&_locker);
    _queue.push_back(item);
}

template <typename Item>
bool ThreadQueue<Item>::Pop(Item *item)
{
    ThreadLocker::Locker lock(&_locker);
    if (_queue.empty())
    {
        return false;
    }
    else
    {
        *item = _queue.front();
        _queue.pop_front();

        return true;
    }
}

template <typename Item>
bool ThreadQueue<Item>::Empty() const
{
    ThreadLocker::Locker lock(&_locker);
    return _queue.empty();
}

#endif
