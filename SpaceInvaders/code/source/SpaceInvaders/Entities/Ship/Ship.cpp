#include "Ship.h"
#include "../../GameContext.h"

#include <cmath>
#include <algorithm>

namespace spaceinv
{
namespace entities
{

Ship::Ship(const GameContext& i_context)
	: states::ReadyToFireShipState(i_context.GetInput())
	, states::RechargingFireState()
	, m_spriteRenderer(i_context.GetSpriteRenderer())
	, m_input(i_context.GetInput())
	, m_displaySize(i_context.GetDisplay().GetSize())
	, m_minX(0.f)
	, m_maxX(static_cast<Position::ValueT>(m_displaySize.w-m_spriteRenderer.GetSpriteSize().w))
	, m_position()
	, m_spriteSize(i_context.GetSpriteRenderer().GetSpriteSize())
	, m_stateMachine(*this, GetInitialState())
{
	const float x = std::roundf((m_displaySize.w - m_spriteSize.w) / 2.f);
	const float y = static_cast<float>(m_displaySize.h - m_spriteSize.h);
	m_position.Set(x, y);
}


void Ship::Update(Seconds i_deltaTime)
{
	Move(i_deltaTime);
	m_stateMachine.CheckCurrentState();
	const ShipState<Ship>& state = m_stateMachine.GetCurrentState();
	(this->*state.Update)(i_deltaTime);
}

void Ship::Move(Seconds i_deltaTime)
{
	static const float k_speed = 500;
	const Position::ValueT shift = static_cast<Position::ValueT>(k_speed * i_deltaTime);
	const platform::Input::ValueT leftValue = m_input.GetAction(platform::Input::Action::Left);
	const platform::Input::ValueT rightValue = m_input.GetAction(platform::Input::Action::Right);
	Position::ValueT x = m_position.GetX();
	x += shift * rightValue - shift * leftValue;
	x = std::min(std::max(m_minX, x), m_maxX);
	m_position.SetX(x);
}

void Ship::Render() const
{
	m_spriteRenderer.Render(graphics::SpriteRenderer::Sprite::Player, m_position);
}

bool Ship::CheckFireStatus()
{
	if (m_fired)
	{
		m_fired = false;
		return true;
	}
	return false;
}

ShipState<spaceinv::entities::Ship> Ship::GetInitialState() const
{
	return GetReadyToFireState();
}
}
}