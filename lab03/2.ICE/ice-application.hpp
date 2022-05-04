#pragma once
#include <sdl-application.hpp>
#include "ice-window.hpp"

class ICEApplication: public SDLApplication
{
public:
	void Run() override
	{
		m_window.Run();
	}

private:
	ICEWindow m_window;
};
