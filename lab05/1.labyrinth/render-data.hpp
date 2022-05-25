#pragma once
#include <gl-texture.hpp>
#include <vector>

class Block
{
public:
	explicit Block(char const *filename)
		:m_texture(filename)
	{}

	void Render(GLfloat x, GLfloat z) const;

private:
	GLTexture2D m_texture;
};

class Earth
{
public:
	explicit Earth(char const *filename)
		:m_texture(filename)
	{}

	void Render(std::pair<GLshort, GLshort> x, std::pair<GLshort, GLshort> z) const;

private:
	GLTexture2D m_texture;
};

struct RenderData
{
	std::vector<Block> blocks;
	Earth earth;
};
