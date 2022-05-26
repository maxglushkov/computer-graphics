#include <utility>
#include "bezier-window.hpp"
#include "cubic-bezier.hpp"

constexpr static int MARKER_HALF_SIZE = 5;

static void RenderAxis(GLfloat length, GLfloat markerWidth, GLfloat markerHalfHeight)
{
	glBegin(GL_LINES);
	glVertex2f(-length, 0.f);
	glVertex2f(length, 0.f);

	const auto range = std::pair<GLshort, GLshort>(-length, length - markerWidth);
	for (GLshort i = range.first; i <= range.second; ++i)
	{
		glVertex2f(i, -markerHalfHeight);
		glVertex2f(i, markerHalfHeight);
	}

	GLContext::AddXArrowMarker(length - markerWidth, length, 0.f, markerHalfHeight);
	glEnd();
}

static void RenderAxes(GLfloat length, GLfloat markerWidth, GLfloat markerHalfHeight)
{
	constexpr static GLfloat Y_AXIS_MODELVIEW[]{
		0.f, 1.f, 0.f, 0.f,
		-1.f, 0.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	};

	glLoadMatrixf(Y_AXIS_MODELVIEW);
	RenderAxis(length, markerWidth, markerHalfHeight);

	glLoadIdentity();
	RenderAxis(length, markerWidth, markerHalfHeight);
}

static void RenderRefPoints(Vector2f const(&p)[CubicBezier::N_REF_POINTS], GLfloat markerHalfSize)
{
	glBegin(GL_LINES);
	for (auto & v: p)
	{
		GLContext::AddCrossMarker(v[0], v[1], markerHalfSize);
	}
	glEnd();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple(5, 0xaaaa);
	glBegin(GL_LINE_STRIP);
	for (auto & v: p)
	{
		glVertex2fv(v);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);
}

static void RenderCurve(CubicBezier const& curve)
{
	constexpr static unsigned POINTS = 300;

	glBegin(GL_LINE_STRIP);
	for (GLushort t = 0; t <= POINTS; ++t)
	{
		glVertex2fv(curve.GetPoint(float(t) / float(POINTS)));
	}
	glEnd();
}

BezierWindow::BezierWindow(CubicBezier & curve, GLdouble resolution)
	:GLSingleWindow("Bezier", 600, 600, resolution, resolution)
	,m_curve(curve)
	,m_resolution(resolution)
{
	glClearColor(1.f, 1.f, 1.f, 0.f);
}

bool BezierWindow::RenderFrame()
{
	const GLfloat markerHalfSize = GetContext().ScreenToGL(MARKER_HALF_SIZE);

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3ub(0, 0, 0);
	RenderAxes(m_resolution - markerHalfSize, 2.f * markerHalfSize, markerHalfSize);

	RenderRefPoints(m_curve.p, markerHalfSize);

	glColor3ub(0, 0, 255);
	RenderCurve(m_curve);
	return true;
}

void BezierWindow::OnMouseMotion(SDL_MouseMotionEvent const& event)
{
	m_controller.UpdateDrag(GetContext(), {event.xrel, event.yrel});
}

void BezierWindow::OnMouseButtonDown(SDL_MouseButtonEvent const& event)
{
	if (event.button == SDL_BUTTON_LEFT)
	{
		m_controller.BeginDrag(GetContext(), m_curve.p, m_curve.N_REF_POINTS, {event.x, event.y}, MARKER_HALF_SIZE);
	}
}

void BezierWindow::OnMouseButtonUp(SDL_MouseButtonEvent const& event)
{
	if (event.button == SDL_BUTTON_LEFT)
	{
		m_controller.EndDrag();
	}
}
