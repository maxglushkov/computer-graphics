#pragma once
#include <bitset>

struct Direction2b: public std::bitset<4>
{
	enum Direction2i
	{
		Right,
		Left,
		Forward,
		Backward
	};
};
