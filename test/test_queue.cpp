/**
* @file   test_queue.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-31 22:18:40
* @brief
**/

#include "thread_queue.h"

class Item
{
};

int main()
{
    ThreadQueue<Item*>::QueueType insert_queue;
    for (size_t i = 0; i < 20; i++)
    {
        Item *item = new Item;
        insert_queue.push_back(item);
    }

    ThreadQueue<Item*> queue;
    queue.Push(insert_queue);

    return 0;
}
