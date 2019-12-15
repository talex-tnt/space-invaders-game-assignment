#include "RechargingFireState.h"
#include "../Ship.h"

namespace spaceinv
{
namespace entities
{
namespace states
{
namespace
{
static const Seconds k_waitTime = 0.3f;
}

RechargingFireState::RechargingFireState() : m_fired(false), m_elapsedTime(0.f) {};

void RechargingFireState::InitRechargingFireState()
{
	m_fired = true;
	m_elapsedTime = 0.f;
}

void RechargingFireState::UpdateRecharginFireState(Seconds i_deltaTime)
{
	m_elapsedTime += i_deltaTime;
}

bool RechargingFireState::IsRecharginFireDone() const
{
	return m_elapsedTime >= k_waitTime;
}

ShipState<spaceinv::entities::Ship> RechargingFireState::GetReadyToFireState() const
{
	return ShipState<Ship>{
			&Ship::UpdateReadyToFire,
			&Ship::InitReadyToFire,
			&Ship::IsReadyToFireDone,
			&Ship::GetFiringState // next state
	};
}

}
}
}