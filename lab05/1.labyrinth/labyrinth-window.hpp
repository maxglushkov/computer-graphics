#pragma once
#include <gl-single-window.hpp>
#include "load-default.hpp"
#include "player-controller.hpp"
#include "render-data.hpp"
struct World;

class LabyrinthWindow: public GLSingleWindow
{
public:
	explicit LabyrinthWindow(World & world);

private:
	World & m_world;
	PlayerController m_controller;
	RenderData m_renderData = LoadDefaultRenderData();

	void RenderFrame() override;

	void OnKeyDown(SDL_KeyboardEvent const& event) override;

	void OnKeyUp(SDL_KeyboardEvent const& event) override;

	void OnMouseMotion(SDL_MouseMotionEvent const& event) override;
};
