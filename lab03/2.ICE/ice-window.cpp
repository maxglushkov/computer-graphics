#include "ice-window.hpp"
#include "ice.hpp"

ICEWindow::ICEWindow()
	:GLSingleWindow("Internal Combustion Engine", 600, 800, 0.5, 1.)
{
	glClearColor(1.f, 1.f, 1.f, 0.f);
}

bool ICEWindow::RenderFrame()
{
	constexpr static double STROKE_DURATION_MS = 500.;

	glClear(GL_COLOR_BUFFER_BIT);

	RenderICE(GetContext(), fmod(SDL_GetTicks64() * M_PI / STROKE_DURATION_MS,  2. * TAU));
	return true;
}
