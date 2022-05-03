#pragma once
#include <gl-single-window.hpp>
#include "vertex-controller.hpp"

struct CubicBezier;

class BezierWindow: public GLSingleWindow
{
public:
	BezierWindow(CubicBezier & curve, GLdouble resolution);

private:
	CubicBezier & m_curve;
	GLdouble m_resolution;
	VertexController m_controller;

	void RenderFrame() override;

	void OnMouseMotion(SDL_MouseMotionEvent const& event) override;

	void OnMouseButtonDown(SDL_MouseButtonEvent const& event) override;

	void OnMouseButtonUp(SDL_MouseButtonEvent const& event) override;
};
