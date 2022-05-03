#pragma once
#include "application.hpp"

class SDLApplication: public IApplication
{
public:
	SDLApplication();

	SDLApplication(SDLApplication const&) = delete;

	~SDLApplication() override;
};
