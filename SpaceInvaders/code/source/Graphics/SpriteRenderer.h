#pragma  once
#include "../Math/Vec2f.h"
#include "../Utils/Types.h"

struct SpaceInvadersEngine;

namespace graphics
{
using SpriteSize = utils::Size;

class SpriteRenderer
{
public:
	using Position = math::Vec2f;
	enum class Sprite : int
	{
		Player,
		Bomb,
		Rocket,
		Enemy1,
		Enemy2
	};

public:
	void Render(Sprite i_sprite, const Position& i_pos) const;
	const SpriteSize& GetSpriteSize() const { return m_spriteSize; }

public:
	SpriteRenderer(const SpaceInvadersEngine& i_engine);

	SpriteRenderer(const SpriteRenderer&) = delete;
	SpriteRenderer(SpriteRenderer&&) = delete;

	SpriteRenderer& operator=(const SpriteRenderer&) = delete;
	SpriteRenderer& operator=(SpriteRenderer&&) = delete;

private:
	const SpaceInvadersEngine& m_engine;
	const SpriteSize m_spriteSize;
};
}