#pragma once
#include <sdl-application.hpp>
#include "bezier-window.hpp"
#include "cubic-bezier.hpp"

class BezierApplication: public SDLApplication
{
public:
	void Run() override
	{
		m_window.Run();
	}

private:
	CubicBezier m_curve{-9.f, -9.f, -3.f, 3.f, 3.f, 9.f, 9.f, 9.f};
	BezierWindow m_window{m_curve, 12.5};
};
