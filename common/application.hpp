#pragma once

struct IApplication
{
	virtual ~IApplication() = default;

	virtual void Run() = 0;
};
