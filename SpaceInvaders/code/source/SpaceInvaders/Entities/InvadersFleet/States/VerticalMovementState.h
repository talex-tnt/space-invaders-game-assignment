#pragma once
#include "../InvadersFleetState.h"
#include "MovementStateBase.h"

namespace spaceinv
{

namespace entities
{
class InvadersFleet;
namespace states
{
class VerticalMovementState : private MovementStateBase
{
public:
	VerticalMovementState(
		const GameContext& i_context, 
		Invader* i_invaders, 
		float& i_speed, 
		std::size_t i_rowCount, 
		std::size_t i_colCount);

	void InitVerticalMovementState();
	void UpdateVerticalMovementState(Seconds i_deltaTime);
	bool IsVerticalMovementDone() const;
	InvadersFleetState<InvadersFleet> GetHorizontalMovementState() const;

public:
	VerticalMovementState(const VerticalMovementState&) = delete;
	VerticalMovementState(VerticalMovementState&&) = delete;

	VerticalMovementState& operator=(const VerticalMovementState&) = delete;
	VerticalMovementState& operator=(VerticalMovementState&&) = delete;

protected:
	~VerticalMovementState() = default;

protected:
	Position::ValueT m_maxVerticalShift;

private:
	Position::ValueT m_maxShift;
	Position::ValueT m_shiftAccumulator;
};
}
}
}