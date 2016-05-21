/**
* @file   task.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-16 00:40:58
* @brief
**/

#ifndef _TASK_H_
#define _TASK_H_

class Task
{
public:
    virtual void Exec() = 0;
    virtual ~Task() {}
};

#endif
