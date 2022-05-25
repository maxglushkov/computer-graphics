#include <gl-context.hpp>
#include "player-controller.hpp"
#include "world.hpp"

constexpr static GLfloat PLAYER_WIDTH = .3f;
constexpr static GLfloat MOVING_SPEED = .03f;
constexpr static GLfloat TURNING_SPEED = M_PI_4;

inline GLfloat CollisionScore(GLfloat player, GLfloat block, GLfloat move)
{
	const GLfloat timeInBlock = (player - block) / move;
	return timeInBlock >= 0.f ? timeInBlock : INFINITY;
}

static void DetectCollisions(Labyrinth const& labyrinth, Vector2f & pos, Vector2f const& move)
{
	const GLshort
		x1 = floor(pos[0] - PLAYER_WIDTH),
		x2 = floor(pos[0] + PLAYER_WIDTH),
		z1 = floor(pos[1] - PLAYER_WIDTH),
		z2 = floor(pos[1] + PLAYER_WIDTH);
	const bool blocks[2][2] = {
		labyrinth.GetBlock(x1, z1) > 0, labyrinth.GetBlock(x2, z1) > 0,
		labyrinth.GetBlock(x1, z2) > 0, labyrinth.GetBlock(x2, z2) > 0
	};

	const short nBlocks = blocks[0][0] + blocks[0][1] + blocks[1][0] + blocks[1][1];
	if (nBlocks > 1)
	{
		if (blocks[0][0] && blocks[1][0])
		{
			pos[0] = round(pos[0]) + PLAYER_WIDTH;
		}
		else if (blocks[0][1] && blocks[1][1])
		{
			pos[0] = round(pos[0]) - PLAYER_WIDTH;
		}
		if (blocks[0][0] && blocks[0][1])
		{
			pos[1] = round(pos[1]) + PLAYER_WIDTH;
		}
		else if (blocks[1][0] && blocks[1][1])
		{
			pos[1] = round(pos[1]) - PLAYER_WIDTH;
		}
	}
	else if (nBlocks == 1)
	{
		Vector2f block = {round(pos[0]), round(pos[1])};
		if (blocks[0][0])
		{
			block += {PLAYER_WIDTH, PLAYER_WIDTH};
		}
		else if (blocks[0][1])
		{
			block += {-PLAYER_WIDTH, PLAYER_WIDTH};
		}
		else if (blocks[1][0])
		{
			block += {PLAYER_WIDTH, -PLAYER_WIDTH};
		}
		else
		{
			block += {-PLAYER_WIDTH, -PLAYER_WIDTH};
		}

		if (CollisionScore(pos[0], block[0], move[0]) < CollisionScore(pos[1], block[1], move[1]))
		{
			pos[0] = block[0];
		}
		else
		{
			pos[1] = block[1];
		}
	}
}

void PlayerController::UpdateYaw(Player & player, GLContext const& ctx, int delta)
{
	player.UpdateEyeDirection(-TURNING_SPEED * ctx.ScreenToGL(delta));
}

void PlayerController::UpdatePosition(Player & player, Labyrinth const& labyrinth) const
{
	if (m_dir.any())
	{
		const Vector2f move = GetMovingDirection(player.GetEyeDirection());
		Vector2f pos = player.GetPosition() + move;
		DetectCollisions(labyrinth, pos, move);
		player.SetPosition(pos);
	}
}

Vector2f PlayerController::GetMovingDirection(Vector2f const& eye) const
{
	Vector2f move = {};
	if (m_dir[Direction2b::Forward])
	{
		move += {eye[0], eye[1]};
	}
	else if (m_dir[Direction2b::Backward])
	{
		move += {-eye[0], -eye[1]};
	}
	if (m_dir[Direction2b::Right])
	{
		move += {-eye[1], eye[0]};
	}
	else if (m_dir[Direction2b::Left])
	{
		move += {eye[1], -eye[0]};
	}
	return MOVING_SPEED * move;
}
