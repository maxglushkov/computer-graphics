#pragma once
#include <direction.hpp>
#include <vector.hpp>
class GLContext;
class Labyrinth;
class Player;

class PlayerController
{
public:
	static void UpdateYaw(Player & player, GLContext const& ctx, int delta);

	void UpdatePosition(Player & player, Labyrinth const& labyrinth) const;

	void StartMoving(Direction2b dir)
	{
		m_dir |= dir;
	}

	void StopMoving(Direction2b dir)
	{
		m_dir &= ~dir;
	}

private:
	Direction2b m_dir;

	Vector2f GetMovingDirection(Vector2f const& eye) const;
};
