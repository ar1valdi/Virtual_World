#pragma once
#include "UtilityStructs.h"

bool operator==(coords a, coords b) {
	if (a.x == b.x && a.y == b.y)
		return true;
	return false;
}