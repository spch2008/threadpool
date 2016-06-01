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

template <typename Item, typename Type = list<Item> >
class ThreadQueue
{
public:
    typedef Type QueueType;

public:
    ThreadQueue() {}
    ~ThreadQueue() {}

    bool Empty() const;
    bool Pop(Item *item);

    void Notify();
    void Push(const Item &item);
    void Push(const QueueType &queue);

protected:
    ThreadQueue(const ThreadQueue &);
    ThreadQueue &operator=(const ThreadQueue &);

private:
    QueueType   _queue;
    mutable ThreadLocker _locker;
};

template <typename Item, typename Type>
void ThreadQueue<Item, Type>::Push(const Item &item)
{
    ThreadLocker::Locker lock(&_locker);
    _queue.push_back(item);
    _locker.Notify();
}

template <typename Item, typename Type>
void ThreadQueue<Item, Type>::Push(const QueueType &queue)
{
    ThreadLocker::Locker lock(&_locker);
    typename QueueType::const_iterator iter = queue.begin();
    for ( ; iter != queue.end(); iter++)
    {
        _queue.push_back(*iter);
        _locker.Notify();
    }
}

template <typename Item, typename Type>
bool ThreadQueue<Item, Type>::Pop(Item *item)
{
    ThreadLocker::Locker lock(&_locker);
    if (_queue.empty())
    {
        _locker.Wait();
    }

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

template <typename Item, typename Type>
bool ThreadQueue<Item, Type>::Empty() const
{
    ThreadLocker::Locker lock(&_locker);
    return _queue.empty();
}

template <typename Item, typename Type>
void ThreadQueue<Item, Type>::Notify()
{
    ThreadLocker::Locker lock(&_locker);
    _locker.NotifyAll();
}

#endif
