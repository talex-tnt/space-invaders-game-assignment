#pragma once
#include "MovementStateBase.h"
#include "../InvadersFleetState.h"
#include "../../../../Utils/Types.h"
#include <cstddef>

namespace spaceinv
{
class GameContext;

namespace entities
{
class Invader;
class InvadersFleet;
namespace states
{
class HorizontalMovementState : private MovementStateBase
{
public:
	HorizontalMovementState(
		const GameContext& i_context, 
		Invader* i_invaders, 
		float& i_speed, 
		std::size_t i_rowCount, 
		std::size_t i_colCount);

	void InitHorizontalMovementState();
	void UpdateHorizontalMovementState(Seconds i_deltaTime);
	bool IsHorizontalMovementDone() const;
	InvadersFleetState<InvadersFleet> GetVerticalMovementState() const;

public:
	HorizontalMovementState(const HorizontalMovementState&) = delete;
	HorizontalMovementState(HorizontalMovementState&&) = delete;

	HorizontalMovementState& operator=(const HorizontalMovementState&) = delete;
	HorizontalMovementState& operator=(HorizontalMovementState&&) = delete;

	void MoveFleet(Position::ValueT shift);
	bool RightMarginReached(Position::ValueT shift, Position::ValueT rightX) const;
	bool LeftMarginReached(Position::ValueT shift, Position::ValueT rightX) const;

protected:
	~HorizontalMovementState() = default;

private:
	const Position::ValueT m_minX;
	const Position::ValueT m_maxX;
};
}
}
}