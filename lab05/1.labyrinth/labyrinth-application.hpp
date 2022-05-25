#pragma once
#include <sdl-application.hpp>
#include "labyrinth-window.hpp"
#include "world.hpp"

class LabyrinthApplication: public SDLApplication
{
public:
	void Run() override
	{
		m_window.Run();
	}

private:
	World m_world = LoadDefaultWorld();
	LabyrinthWindow m_window{m_world};
};
