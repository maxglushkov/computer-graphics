#include "load-default.hpp"
#include "render-data.hpp"
#include "world.hpp"

constexpr static std::initializer_list<char const*> BLOCK_TEXTURES = {
	"1.png",
	"2.png",
	"3.png",
	"4.png",
	"5.png",
	"6.png"
};
constexpr static char EARTH_TEXTURE[] = "earth.png";

constexpr static Labyrinth::Header LABYRINTH_HEADER = {
	.xMin = -16, .xMax = 16,
	.zMin = -16, .zMax = 16
};
constexpr static std::initializer_list<GLubyte> LABYRINTH_BLOCKS = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 1,
	1, 1, 1, 0, 2, 2, 2, 0, 2, 4, 4, 4, 4, 0, 3, 2, 2, 2, 2, 0, 5, 5, 5, 0, 2, 0, 2, 0, 2, 0, 4, 0, 0,
	1, 0, 1, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 5, 0, 2, 0, 2, 2, 2, 0, 4, 4, 1,
	1, 0, 1, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 3, 0, 4, 4, 4, 4, 4, 0, 5, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 2, 0, 2, 0, 0, 0, 2, 2, 2, 0, 3, 0, 0, 0, 0, 0, 4, 0, 5, 0, 2, 0, 1, 0, 3, 3, 4, 0, 1,
	1, 0, 0, 0, 0, 0, 2, 0, 3, 0, 0, 0, 0, 0, 3, 0, 2, 2, 2, 0, 4, 0, 5, 0, 2, 0, 1, 0, 3, 0, 4, 0, 1,
	1, 1, 1, 1, 1, 0, 2, 0, 3, 3, 3, 0, 3, 3, 3, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1, 0, 3, 0, 4, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 0, 1, 1, 1, 1, 0, 3, 0, 4, 0, 1,
	1, 0, 4, 4, 4, 4, 4, 0, 3, 3, 3, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 1,
	1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 5, 5, 5, 5, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 1,
	1, 0, 3, 0, 3, 0, 2, 5, 5, 5, 5, 5, 5, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 3, 0, 3, 0, 2, 0, 5, 0, 0, 0, 5, 0, 4, 0, 5, 0, 5, 5, 5, 5, 5, 0, 3, 3, 3, 3, 0, 3, 3, 3, 1,
	1, 0, 3, 3, 3, 0, 2, 0, 5, 0, 4, 0, 5, 0, 4, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 4, 0, 5, 0, 6, 6, 0, 6, 6, 0, 4, 0, 3, 0, 2, 2, 2, 0, 5, 1, 1, 0, 1,
	1, 2, 2, 0, 2, 2, 2, 0, 3, 3, 4, 0, 0, 0, 6, 0, 0, 0, 6, 0, 4, 0, 3, 0, 2, 0, 0, 0, 5, 0, 1, 0, 1,
	1, 0, 2, 0, 0, 0, 0, 0, 0, 3, 4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 5, 5, 5, 0, 1, 0, 1,
	1, 0, 2, 0, 2, 2, 2, 2, 0, 3, 0, 0, 3, 0, 6, 0, 0, 0, 6, 0, 2, 0, 3, 0, 2, 0, 0, 0, 2, 0, 1, 0, 1,
	1, 0, 2, 0, 0, 0, 2, 0, 0, 3, 0, 3, 3, 0, 6, 6, 0, 6, 6, 0, 2, 0, 3, 0, 2, 0, 3, 0, 2, 0, 0, 0, 1,
	1, 0, 2, 2, 2, 2, 2, 0, 3, 3, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 3, 0, 2, 4, 4, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 0, 2, 2, 2, 2, 2, 0, 3, 0, 0, 0, 0, 0, 1,
	1, 4, 4, 4, 0, 4, 4, 4, 4, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 2, 0, 5, 5, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 5, 5, 5, 5, 0, 4, 4, 4, 4, 4, 4, 0, 3, 3, 3, 3, 0, 2, 0, 5, 0, 1,
	1, 2, 2, 2, 0, 5, 5, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 2, 0, 5, 0, 1,
	1, 0, 0, 2, 0, 0, 0, 5, 0, 4, 0, 2, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0, 5, 0, 4, 0, 5, 2, 2, 0, 0, 0, 1,
	1, 0, 2, 2, 0, 2, 0, 5, 5, 4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 5, 0, 4, 0, 5, 0, 0, 0, 2, 2, 1,
	1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 2, 0, 3, 3, 0, 5, 0, 5, 0, 3, 0, 5, 0, 4, 0, 5, 0, 3, 0, 2, 0, 1,
	1, 2, 2, 3, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 0, 0, 5, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0, 3, 0, 2, 0, 1,
	1, 2, 0, 3, 0, 0, 0, 4, 0, 0, 0, 0, 0, 4, 4, 4, 5, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 3, 0, 2, 0, 1,
	1, 0, 0, 3, 0, 3, 0, 4, 0, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1,
	1, 0, 2, 3, 0, 3, 0, 4, 0, 5, 0, 5, 0, 2, 2, 0, 5, 0, 2, 2, 2, 2, 3, 3, 3, 0, 4, 0, 3, 3, 3, 0, 1,
	1, 0, 0, 0, 0, 3, 0, 0, 0, 5, 0, 0, 0, 2, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
constexpr static Vector2f PLAYER_POSITION = {.5f, .5f};
constexpr static GLfloat PLAYER_YAW = .0f;

RenderData LoadDefaultRenderData()
{
	std::vector<Block> blocks;
	blocks.reserve(BLOCK_TEXTURES.size());
	for (const auto filename: BLOCK_TEXTURES)
	{
		blocks.emplace_back(filename);
	}

	return {
		.blocks = std::move(blocks),
		.earth = Earth(EARTH_TEXTURE)
	};
}

World LoadDefaultWorld()
{
	return {
		.labyrinth = {LABYRINTH_HEADER, LABYRINTH_BLOCKS},
		.player = {PLAYER_POSITION, PLAYER_YAW}
	};
}