#pragma once
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
class MovementStateBase
{
public:
	MovementStateBase(Invader* i_invaders, float& i_speed, std::size_t i_rowCount, std::size_t i_colCount);

public:
	MovementStateBase(const MovementStateBase&) = delete;
	MovementStateBase(MovementStateBase&&) = delete;

	MovementStateBase& operator=(const MovementStateBase&) = delete;
	MovementStateBase& operator=(MovementStateBase&&) = delete;


protected:
	~MovementStateBase() = default;

	const Invader& GetFirstInvader() const;
	const Invader& GetLastInvader() const;

protected:
	Invader* m_invaders;
	const std::size_t m_rowCount;
	const std::size_t m_colCount;
	float& m_speedRef;
	bool m_isDone;
};
}
}
}