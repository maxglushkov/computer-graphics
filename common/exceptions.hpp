#pragma once
#include <SDL_error.h>
#include <stdexcept>

class LastSDLError: public std::runtime_error
{
public:
	LastSDLError()
		:std::runtime_error(SDL_GetError())
	{}
};
