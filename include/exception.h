/**
* @file   exception.h
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-13 11:06:11
* @brief
**/

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>
#include <exception>

using std::string;
using std::exception;

class Exception : public exception
{
public:
    explicit Exception(const string &text);
    Exception(const string &text, int code);
    ~Exception() throw();

    const char *what() const throw();

private:
    string _text;
    int    _code;
};

#endif
