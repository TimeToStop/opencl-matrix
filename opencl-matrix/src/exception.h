#pragma once

#include <exception>

#include <string>

class Exception : public std::exception
{
public:
	Exception(const std::string& msg);
	virtual ~Exception();

	virtual const char* what() const noexcept override;

private:
	std::string _msg;
};

