#pragma once
#include <vector.hpp>

struct CubicBezier
{
	constexpr static size_t N_REF_POINTS = 4;

	Vector2f p[N_REF_POINTS];

	Vector2f GetPoint(GLclampf t) const;
};
