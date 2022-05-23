#pragma once
#include <math.h>
#include "vector.hpp"

constexpr double TAU = 2. * M_PI;

class GLContext
{
public:
	GLContext(bool isFrustum, GLdouble xRes, GLdouble yRes, GLdouble zNear, GLdouble zFar)
		:m_isFrustum(isFrustum)
		,m_xRes(xRes)
		,m_yRes(yRes)
		,m_zNear(zNear)
		,m_zFar(zFar)
	{}

	static void AddCrossMarker(GLfloat xc, GLfloat yc, GLfloat halfSize);

	static void AddXArrowMarker(GLfloat xFrom, GLfloat xTo, GLfloat yc, GLfloat halfHeight);

	static void FillRectangle(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

	void AddArc(GLfloat xc, GLfloat yc, GLfloat r, GLfloat angle1, GLfloat angle2) const;

	void FillCircle(GLfloat xc, GLfloat yc, GLfloat r) const;

	void SetScreenSize(int width, int height);

	GLfloat ScreenToGL(int screen) const
	{
		return screen * m_screenToGL;
	}

	int GLToScreen(GLfloat gl) const
	{
		return gl / m_screenToGL;
	}

	Vector2f ScreenPointToGL(Vector2i const& screen) const
	{
		return {
			GLfloat(m_left) + ScreenToGL(screen[0]),
			GLfloat(m_top) - ScreenToGL(screen[1])
		};
	}

private:
	bool m_isFrustum;
	GLdouble m_xRes, m_yRes;
	GLdouble m_zNear, m_zFar;
	GLdouble m_left, m_top;
	GLdouble m_screenToGL;
};
