#include <SDL_image.h>
#include "exceptions.hpp"
#include "gl-texture.hpp"

GLTexture2D::GLTexture2D(char const* filename)
{
	SDL_Surface *const image = IMG_Load(filename);
	if (!image)
	{
		throw LastSDLError();
	}
	if (image->format->BytesPerPixel != 4)
	{
		throw std::runtime_error("Only RGBA textures are supported");
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	SDL_FreeSurface(image);
}
