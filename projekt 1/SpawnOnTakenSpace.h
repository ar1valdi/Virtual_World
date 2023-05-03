#pragma once
#include <iostream>
#include <string>

class SpawnOnTakenSpace : std::exception
{
private:
	std::string msg;
public:
	SpawnOnTakenSpace(const std::string& msg = "Tried to spawn organism on taken space") : msg(msg) {}
	const char* what() const noexcept override {
		return msg.c_str();
	}
};