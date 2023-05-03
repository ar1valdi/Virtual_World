#pragma once

struct coords {
	int x = 0;
	int y = 0;

	bool operator==(coords sec) {
		if (x == sec.x && y == sec.y)
			return true;
		return false;
	}
};
