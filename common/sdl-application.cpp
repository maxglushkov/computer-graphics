#include <SDL.h>
#include "exceptions.hpp"
#include "sdl-application.hpp"

SDLApplication::SDLApplication()
{
	if (SDL_WasInit(SDL_INIT_EVERYTHING))
	{
		throw std::logic_error("Only one instance of SDLApplication is permitted");
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw LastSDLError();
	}
}

SDLApplication::~SDLApplication()
{
	SDL_Quit();
}
