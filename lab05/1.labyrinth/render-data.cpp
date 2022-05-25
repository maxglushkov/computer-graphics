#include "render-data.hpp"

constexpr static GLfloat BLOCK_WIDTH = 1.f;
constexpr static GLfloat BLOCK_HEIGHT = 2.f;

void Block::Render(GLfloat x, GLfloat z) const
{
	const GLfloat x2 = x + BLOCK_WIDTH;
	const GLfloat z2 = z + BLOCK_WIDTH;

	m_texture.Bind();

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(x, BLOCK_HEIGHT, z);
	glTexCoord2f(0.f, BLOCK_HEIGHT);
	glVertex3f(x, 0.f, z);
	glTexCoord2f(BLOCK_WIDTH, 0.f);
	glVertex3f(x, BLOCK_HEIGHT, z2);
	glTexCoord2f(BLOCK_WIDTH, BLOCK_HEIGHT);
	glVertex3f(x, 0.f, z2);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(x2, BLOCK_HEIGHT, z2);
	glTexCoord2f(0.f, BLOCK_HEIGHT);
	glVertex3f(x2, 0.f, z2);
	glTexCoord2f(BLOCK_WIDTH, 0.f);
	glVertex3f(x2, BLOCK_HEIGHT, z);
	glTexCoord2f(BLOCK_WIDTH, BLOCK_HEIGHT);
	glVertex3f(x2, 0.f, z);
	glTexCoord2f(0.f, 0.f);
	glVertex3f(x, BLOCK_HEIGHT, z);
	glTexCoord2f(0.f, BLOCK_HEIGHT);
	glVertex3f(x, 0.f, z);
	glEnd();
}

void Earth::Render(std::pair<GLshort, GLshort> x, std::pair<GLshort, GLshort> z) const
{
	x.second += BLOCK_WIDTH;
	z.second += BLOCK_WIDTH;

	m_texture.Bind();

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(x.first, z.first);
	glVertex3f(x.first, 0.f, z.first);
	glTexCoord2f(x.first, z.second);
	glVertex3f(x.first, 0.f, z.second);
	glTexCoord2f(x.second, z.first);
	glVertex3f(x.second, 0.f, z.first);
	glTexCoord2f(x.second, z.second);
	glVertex3f(x.second, 0.f, z.second);
	glEnd();
}
