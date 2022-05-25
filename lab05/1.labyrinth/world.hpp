#pragma once
#include <cmath>
#include <functional>
#include <vector.hpp>

class Labyrinth
{
public:
	struct Header
	{
		GLshort xMin, xMax;
		GLshort zMin, zMax;
	};

	Labyrinth(Header const& header, std::vector<GLubyte> && blocks)
		:m_header(header)
		,m_stride(int(m_header.xMax) - m_header.xMin + 1)
		,m_center(-m_header.zMin * m_stride - m_header.xMin)
		,m_blocks(std::move(blocks))
	{}

	std::pair<GLshort, GLshort> GetXRange() const
	{
		return {m_header.xMin, m_header.xMax};
	}

	std::pair<GLshort, GLshort> GetZRange() const
	{
		return {m_header.zMin, m_header.zMax};
	}

	GLubyte GetBlock(GLshort x, GLshort z) const
	{
		if (x < m_header.xMin || x > m_header.xMax
		 || z < m_header.zMin || z > m_header.zMax)
		{
			return 0;
		}
		return m_blocks[m_center + x + z * m_stride];
	}

	void ForEachNotAir(std::function<void(GLshort x, GLshort z, GLubyte block)> f) const;

private:
	Header m_header;
	int m_stride, m_center;
	std::vector<GLubyte> m_blocks;
};

class Player
{
public:
	Player(Vector2f const& position, GLfloat yaw)
		:m_position{position}
		,m_yaw{yaw}
	{}

	Vector2f GetPosition() const
	{
		return m_position;
	}

	Vector2f GetEyeDirection() const
	{
		return {sinf(m_yaw), cosf(m_yaw)};
	}

	void SetPosition(Vector2f const& position)
	{
		m_position = position;
	}

	void UpdateEyeDirection(GLfloat dYaw)
	{
		m_yaw += dYaw;
	}

private:
	Vector2f m_position;
	GLfloat m_yaw;
};

struct World
{
	Labyrinth labyrinth;
	Player player;
};
