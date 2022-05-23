#pragma once
#include <GL/gl.h>
#include <utility>

class GLTexture2D
{
public:
	explicit GLTexture2D(char const* filename);

	GLTexture2D(GLTexture2D const&) = delete;
	GLTexture2D(GLTexture2D && other)
	{
		MoveUninit(std::move(other));
	}

	~GLTexture2D()
	{
		Drop();
	}

	GLTexture2D & operator =(GLTexture2D const&) = delete;
	GLTexture2D & operator =(GLTexture2D && other)
	{
		Drop();
		MoveUninit(std::move(other));
		return *this;
	}

	void Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}

private:
	GLuint m_texture;

	void Drop()
	{
		glDeleteTextures(1, &m_texture);
	}

	void MoveUninit(GLTexture2D && from)
	{
		m_texture = from.m_texture;
		from.m_texture = 0;
	}
};
