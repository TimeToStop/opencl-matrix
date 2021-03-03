#include "exception.h"

Exception::Exception(const std::string& msg):
    _msg(msg)
{
}

Exception::~Exception()
{
}

const char* Exception::what() const noexcept
{
    return _msg.c_str();
}
