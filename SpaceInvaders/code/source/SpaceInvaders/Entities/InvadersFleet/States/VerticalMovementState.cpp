#include "VerticalMovementState.h"
#include "../InvadersFleet.h"
#include "../../../GameContext.h"

namespace spaceinv
{
namespace entities
{
namespace states
{

VerticalMovementState::VerticalMovementState(
	const GameContext& i_context,
	Invader* i_invaders,
	float& i_speed,
	std::size_t i_rowCount,
	std::size_t i_colCount)
	: MovementStateBase(i_invaders, i_speed, i_rowCount, i_colCount)
	, m_maxShift(static_cast<Position::ValueT>(i_context.GetSpriteRenderer().GetSpriteSize().h))
	, m_shiftAccumulator(0.f)
{ }

void VerticalMovementState::InitVerticalMovementState()
{
	m_maxVerticalShift= m_maxShift;
	m_shiftAccumulator = 0.f;
}

void VerticalMovementState::UpdateVerticalMovementState(Seconds i_deltaTime)
{
	const Position::ValueT positiveSpeed = std::abs(m_speedRef); // we always move down
	const Position::ValueT shift = static_cast<Position::ValueT>(positiveSpeed * i_deltaTime);
	for (std::size_t i = 0; i < m_rowCount; ++i)
	{
		for (std::size_t j = 0; j < m_colCount; ++j)
		{
			Invader& invader = *((m_invaders + i * m_colCount) + j);
			Position::ValueT& y = invader.GetPosition().GetY();
			y += shift;
		}
	}
	m_shiftAccumulator += shift;
}

bool VerticalMovementState::IsVerticalMovementDone() const
{
	return m_shiftAccumulator >= m_maxVerticalShift;
}

InvadersFleetState<spaceinv::entities::InvadersFleet> VerticalMovementState::GetHorizontalMovementState() const
{
	return InvadersFleetState<InvadersFleet>{
			&InvadersFleet::UpdateHorizontalMovementState,
			&InvadersFleet::InitHorizontalMovementState,
			&InvadersFleet::IsHorizontalMovementDone,
			&InvadersFleet::GetVerticalMovementState // next state
	};
}

}
}
}