#pragma once
#include <gl-single-window.hpp>

class ICEWindow: public GLSingleWindow
{
public:
	ICEWindow();

private:
	bool RenderFrame() override;
};
