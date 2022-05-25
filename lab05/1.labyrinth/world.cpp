#include "world.hpp"

void Labyrinth::ForEachNotAir(std::function<void(GLshort x, GLshort z, GLubyte block)> f) const
{
	GLubyte const* block = m_blocks.data();
	for (GLshort z = m_header.zMin; z <= m_header.zMax; ++z)
	{
		for (GLshort x = m_header.xMin; x <= m_header.xMax; ++x, ++block)
		{
			if (*block)
			{
				f(x, z, *block);
			}
		}
	}
}
