#pragma once
#include <iostream>
#include <string>

class InvalidType : std::exception
{
private:
	std::string msg;
public:
	InvalidType(const std::string& msg="Invalid type of object") : msg(msg) {}
	const char* what() const noexcept override {
		return msg.c_str();
	}
};