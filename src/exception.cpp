/**
* @file   exception.cpp
* @author sunpengcheng(spch2008@foxmail.com)
* @date   2016-05-13 11:06:11
* @brief
**/

#include "exception.h"
#include <string.h>

Exception::Exception(const string &text)
    : _text(text), _code(0)
{
}

Exception::Exception(const string &text, int code)
{
    _text = text + strerror(code);
    _code = code;
}

Exception::~Exception() throw()
{
}

const char *Exception::what() const throw()
{
    return _text.c_str();
}

