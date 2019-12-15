#include "SpriteRenderer.h"
#include "../Engine.h"
#include <cmath>
#include <type_traits>

namespace
{
Engine& GetEngine(const Engine& i_engine)
{
	return *const_cast<Engine*>(&i_engine); // #todo: ask why some engine's methods are not const qualified
}
template<class T>
constexpr typename std::underlying_type<T>::type GetValue(const T& i_enum)
{
	return static_cast<typename std::underlying_type<T>::type>(i_enum);
}
}

namespace graphics
{

SpriteRenderer::SpriteRenderer(const Engine& i_engine) 
	: m_engine(i_engine), m_spriteSize{Engine::SpriteSize, Engine::SpriteSize}
{ 
	static_assert(GetValue(Sprite::Player) == GetValue(Engine::Sprite::Player), "Renderer::Sprite Enum Type Mismatch");
	static_assert(GetValue(Sprite::Bomb) == GetValue(Engine::Sprite::Bomb), "Renderer::Sprite Enum Type Mismatch");
	static_assert(GetValue(Sprite::Rocket) == GetValue(Engine::Sprite::Rocket), "Renderer::Sprite Enum Type Mismatch");
	static_assert(GetValue(Sprite::Enemy1) == GetValue(Engine::Sprite::Enemy1), "Renderer::Sprite Enum Type Mismatch");
	static_assert(GetValue(Sprite::Enemy2) == GetValue(Engine::Sprite::Enemy2), "Renderer::Sprite Enum Type Mismatch");
}

void SpriteRenderer::Render(Sprite i_sprite, const Position& i_pos) const
{
	GetEngine(m_engine).RenderSprite(
		static_cast<Engine::Sprite>(i_sprite), 
		static_cast<int>(std::round(i_pos.GetX())),
		static_cast<int>(std::round(i_pos.GetY())));
}

}