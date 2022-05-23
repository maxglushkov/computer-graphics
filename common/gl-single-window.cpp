#include "exceptions.hpp"
#include "gl-single-window.hpp"

static SDL_Window *window;
static SDL_GLContext context;

GLSingleWindow::GLSingleWindow(
	char const* title,
	int width, int height,
	GLdouble xRes, GLdouble yRes,
	GLdouble zNear, GLdouble zFar,
	bool isFrustum
)
	:m_ctx(isFrustum, xRes, yRes, zNear, zFar)
{
	if (window)
	{
		throw std::logic_error("Only one instance of GLSingleWindow is permitted");
	}
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	if (!window)
	{
		throw LastSDLError();
	}

	context = SDL_GL_CreateContext(window);
	if (!context)
	{
		throw LastSDLError();
	}
	m_ctx.SetScreenSize(width, height);
}

GLSingleWindow::~GLSingleWindow()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

void GLSingleWindow::Run()
{
	SDL_Event event;
	for (;;)
	{
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					OnKeyDown(event.key);
					break;
				case SDL_KEYUP:
					OnKeyUp(event.key);
					break;
				case SDL_MOUSEMOTION:
					OnMouseMotion(event.motion);
					break;
				case SDL_MOUSEBUTTONDOWN:
					OnMouseButtonDown(event.button);
					break;
				case SDL_MOUSEBUTTONUP:
					OnMouseButtonUp(event.button);
					break;
				case SDL_QUIT:
					return;
			}
		}
		else
		{
			RenderFrame();
			SDL_GL_SwapWindow(window);
		}
	}
}
