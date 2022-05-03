#include "cubic-bezier.hpp"

Vector2f CubicBezier::GetPoint(GLclampf t) const
{
	return (1 - t) * (1 - t) * (1 - t) * p[0]
	     + 3 * t * (1 - t) * (1 - t) * p[1]
	     + 3 * t * t * (1 - t) * p[2]
	     + t * t * t * p[3];
}
