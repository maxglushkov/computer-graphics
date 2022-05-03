#include "gl-context.hpp"

void GLContext::AddCrossMarker(GLfloat xc, GLfloat yc, GLfloat halfSize)
{
	glVertex2f(xc - halfSize, yc - halfSize);
	glVertex2f(xc + halfSize, yc + halfSize);
	glVertex2f(xc - halfSize, yc + halfSize);
	glVertex2f(xc + halfSize, yc - halfSize);
}

void GLContext::AddXArrowMarker(GLfloat xFrom, GLfloat xTo, GLfloat yc, GLfloat halfHeight)
{
	glVertex2f(xFrom, yc - halfHeight);
	glVertex2f(xTo, yc);
	glVertex2f(xTo, yc);
	glVertex2f(xFrom, yc + halfHeight);
}

void GLContext::FillRectangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glEnd();
}

void GLContext::AddArc(GLfloat xc, GLfloat yc, GLfloat r, GLfloat angle1, GLfloat angle2)
{
	const GLfloat step = M_PI / GLToScreen(r);
	for (; angle1 < angle2; angle1 += step)
	{
		glVertex2f(xc + r * cos(angle1), yc + r * sin(angle1));
	}
	glVertex2f(xc + r * cos(angle2), yc + r * sin(angle2));
}

void GLContext::FillCircle(GLfloat xc, GLfloat yc, GLfloat r)
{
	glBegin(GL_TRIANGLE_FAN);
	AddArc(xc, yc, r, 0.f, TAU);
	glEnd();
}

void GLContext::SetScreenSize(int width, int height)
{
	const GLdouble xScreenToGL = m_xRes / width;
	const GLdouble yScreenToGL = m_yRes / height;
	if (xScreenToGL < yScreenToGL)
	{
		m_left = -(m_screenToGL = yScreenToGL) * width;
		m_top = m_yRes;
	}
	else
	{
		m_left = -m_xRes;
		m_top = (m_screenToGL = xScreenToGL) * height;
	}
	m_screenToGL *= 2.;

	glMatrixMode(GL_PROJECTION);
	glOrtho(m_left, -m_left, -m_top, m_top, -1., 1.);

	glMatrixMode(GL_MODELVIEW);
}
