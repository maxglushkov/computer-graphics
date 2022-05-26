#include <GL/glu.h>
#include <exceptions.hpp>
#include "labyrinth-window.hpp"
#include "world.hpp"

static Direction2b ScancodeToDirection(SDL_Scancode scancode)
{
	Direction2b dir;
	dir.set(Direction2b::Right, scancode == SDL_SCANCODE_RIGHT);
	dir.set(Direction2b::Left, scancode == SDL_SCANCODE_LEFT);
	dir.set(Direction2b::Forward, scancode == SDL_SCANCODE_UP);
	dir.set(Direction2b::Backward, scancode == SDL_SCANCODE_DOWN);
	return dir;
}

LabyrinthWindow::LabyrinthWindow(World & world)
	:GLSingleWindow("Labyrinth", 600, 600, .24, .24, .18, 20., true)
	,m_world(world)
{
	if (SDL_SetRelativeMouseMode(SDL_TRUE))
	{
		throw LastSDLError();
	}

	glClearColor(.3764705882f, .7058823529f, .9568627451f, 0.f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
}

bool LabyrinthWindow::RenderFrame()
{
	m_controller.UpdatePosition(m_world.player, m_world.labyrinth);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const Vector2f position = m_world.player.GetPosition();
	const Vector2f eyeDirection = m_world.player.GetEyeDirection();
	glLoadIdentity();
	gluLookAt(
		position[0], 1.5, position[1],
		position[0] + eyeDirection[0], 1.5, position[1] + eyeDirection[1],
		0., 1., 0.
	);

	m_renderData.earth.Render(m_world.labyrinth.GetXRange(), m_world.labyrinth.GetZRange());
	m_world.labyrinth.ForEachNotAir(
		[&](GLshort x, GLshort z, GLubyte block)
		{
			m_renderData.blocks[block - 1].Render(x, z);
		}
	);
	return true;
}

void LabyrinthWindow::OnKeyDown(SDL_KeyboardEvent const& event)
{
	m_controller.StartMoving(ScancodeToDirection(event.keysym.scancode));
}

void LabyrinthWindow::OnKeyUp(SDL_KeyboardEvent const& event)
{
	m_controller.StopMoving(ScancodeToDirection(event.keysym.scancode));
}

void LabyrinthWindow::OnMouseMotion(SDL_MouseMotionEvent const& event)
{
	PlayerController::UpdateYaw(m_world.player, GetContext(), event.xrel);
}
