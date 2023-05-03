#pragma once
#include <iostream>
#include <string>

class PosOutOfMap : std::exception
{
private:
	std::string msg;
public:
	PosOutOfMap(const std::string& msg = "Position of obejct is outside the map") : msg(msg) {}
	const char* what() const noexcept override {
		return msg.c_str();
	}
};