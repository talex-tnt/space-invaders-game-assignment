#include "Rocket.h"
#include "../../GameContext.h"

namespace spaceinv
{
namespace entities
{
namespace
{
static const float k_speed = 1000;
static const float k_halfWidth = 2;
}

Rocket::Rocket(const GameContext& i_context)
	: m_spriteRenderer(i_context.GetSpriteRenderer())
	, m_displaySize(i_context.GetDisplay().GetSize())
	, m_size(i_context.GetSpriteRenderer().GetSpriteSize())
	, m_active(false)
{ }

void Rocket::Update(Seconds i_deltaTime)
{
	if (m_active)
	{
		const Position::ValueT shift = static_cast<Position::ValueT>(k_speed * i_deltaTime);
		Position::ValueT y = m_position.GetY();
		y -= shift;
		m_position.SetY(y);
		if (m_position.GetY() + m_size.h < 0.f)
		{
			m_active = false;
		}
	}
}

void Rocket::Render() const
{
	if (m_active)
	{
		m_spriteRenderer.Render(graphics::SpriteRenderer::Sprite::Rocket, m_position);
	}
}

spaceinv::Position Rocket::GetTopLeftMargin() const
{
	return Position(m_position.GetX() + (m_size.w / 2.f) - k_halfWidth, m_position.GetY());
}

spaceinv::Position Rocket::GetBottomRightMargin() const
{
	return Position(m_position.GetX() + (m_size.w / 2.f) + k_halfWidth, m_position.GetY() + m_size.h);
}
}
}