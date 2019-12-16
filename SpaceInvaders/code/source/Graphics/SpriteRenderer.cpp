#include "SpriteRenderer.h"
#include <Game/LegacyEngine/SpaceInvadersEngine.h>
#include <cmath>
#include <type_traits>

namespace
{
template<class T>
constexpr typename std::underlying_type<T>::type GetValue(const T& i_enum)
{
	return static_cast<typename std::underlying_type<T>::type>(i_enum);
}
}

namespace graphics
{

SpriteRenderer::SpriteRenderer(const SpaceInvadersEngine& i_engine)
	: m_engine(i_engine), m_spriteSize{ SpaceInvadersEngine::SpriteSize, SpaceInvadersEngine::SpriteSize}
{ 
	static_assert(GetValue(Sprite::Player) == GetValue(SpaceInvadersEngine::Sprite::Player), "Renderer::Sprite Enum Type Mismatch");
	static_assert(GetValue(Sprite::Bomb) == GetValue(SpaceInvadersEngine::Sprite::Bomb), "Renderer::Sprite Enum Type Mismatch");
	static_assert(GetValue(Sprite::Rocket) == GetValue(SpaceInvadersEngine::Sprite::Rocket), "Renderer::Sprite Enum Type Mismatch");
	static_assert(GetValue(Sprite::Enemy1) == GetValue(SpaceInvadersEngine::Sprite::Enemy1), "Renderer::Sprite Enum Type Mismatch");
	static_assert(GetValue(Sprite::Enemy2) == GetValue(SpaceInvadersEngine::Sprite::Enemy2), "Renderer::Sprite Enum Type Mismatch");
}

void SpriteRenderer::Render(Sprite i_sprite, const Position& i_pos) const
{
	m_engine.RenderSprite(
		static_cast<SpaceInvadersEngine::Sprite>(i_sprite),
		static_cast<int>(std::round(i_pos.GetX())),
		static_cast<int>(std::round(i_pos.GetY())));
}

}