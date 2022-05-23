#pragma once
#include <SDL.h>
#include "gl-context.hpp"

class GLSingleWindow
{
public:
	GLSingleWindow(
		char const* title,
		int width, int height,
		GLdouble xRes, GLdouble yRes,
		GLdouble zNear = -1., GLdouble zFar = 1.,
		bool isFrustum = false
	);

	GLSingleWindow(GLSingleWindow const&) = delete;

	virtual ~GLSingleWindow();

	GLContext & GetContext()
	{
		return m_ctx;
	}

	void Run();

private:
	GLContext m_ctx;

	virtual void RenderFrame() = 0;

	virtual void OnKeyDown(SDL_KeyboardEvent const& event)
	{}
	virtual void OnKeyUp(SDL_KeyboardEvent const& event)
	{}
	virtual void OnMouseMotion(SDL_MouseMotionEvent const& event)
	{}
	virtual void OnMouseButtonDown(SDL_MouseButtonEvent const& event)
	{}
	virtual void OnMouseButtonUp(SDL_MouseButtonEvent const& event)
	{}
};
