#include "HorizontalMovementState.h"
#include "../InvadersFleet.h"
#include "../../Invader/Invader.h"
#include "../../../GameContext.h"


namespace spaceinv
{
namespace entities
{
namespace states
{
namespace 
{
static const float k_speedFactor = 1.3f;
}

HorizontalMovementState::HorizontalMovementState(
	const GameContext& i_context, 
	Invader* i_invaders, 
	float& i_speed,
	std::size_t i_rowCount, 
	std::size_t i_colCount)
	: MovementStateBase(i_invaders, i_speed, i_rowCount, i_colCount)
	, m_minX(0.f)
	, m_maxX(static_cast<Position::ValueT>(i_context.GetDisplay().GetSize().w - i_context.GetSpriteRenderer().GetSpriteSize().w))
{ }

void HorizontalMovementState::InitHorizontalMovementState()
{
	m_isDone = false;
}

void HorizontalMovementState::UpdateHorizontalMovementState(Seconds i_deltaTime)
{
	Position::ValueT shift = static_cast<Position::ValueT>(m_speedRef * i_deltaTime);
	const Position::ValueT rightX = GetLastInvader().GetPosition().GetX();
	const Position::ValueT leftX = GetFirstInvader().GetPosition().GetX();
	if (RightMarginReached(shift, rightX))
	{
		shift = m_maxX - rightX;
		m_speedRef *= -k_speedFactor;
		m_isDone = true;
	}
	else if (LeftMarginReached(shift, leftX))
	{
		shift = m_minX - leftX;
		m_speedRef *= -k_speedFactor;
		m_isDone = true;
	}
	MoveFleet(shift);
}

bool HorizontalMovementState::RightMarginReached(Position::ValueT shift, Position::ValueT rightX) const
{
	const Position::ValueT rightMostPos = rightX + shift;
	return m_speedRef > 0.f && rightMostPos > m_maxX;
}

bool HorizontalMovementState::LeftMarginReached(Position::ValueT shift, Position::ValueT leftX) const
{
	const Position::ValueT leftMostPos = leftX + shift;
	return m_speedRef < 0.f && leftMostPos < m_minX;
}

void HorizontalMovementState::MoveFleet(Position::ValueT shift)
{
	for (std::size_t i = 0; i < m_rowCount; ++i)
	{
		for (std::size_t j = 0; j < m_colCount; ++j)
		{
			Invader& invader = *((m_invaders + i * m_colCount) + j);
			Position::ValueT& x = invader.GetPosition().GetX();
			x += shift;
		}
	}
}

bool HorizontalMovementState::IsHorizontalMovementDone() const
{
	return m_isDone;
}

InvadersFleetState<spaceinv::entities::InvadersFleet> HorizontalMovementState::GetVerticalMovementState() const
{
	return InvadersFleetState<InvadersFleet>{
			&InvadersFleet::UpdateVerticalMovementState,
			&InvadersFleet::InitVerticalMovementState,
			&InvadersFleet::IsVerticalMovementDone,
			&InvadersFleet::GetHorizontalMovementState // next state
	};
}

}
}
}