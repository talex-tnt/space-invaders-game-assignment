#include "ReadyToFireShipState.h"
#include "../Ship.h"
#include "../../../../Platform/Input.h"

namespace spaceinv
{
namespace entities
{
namespace states
{

ReadyToFireShipState::ReadyToFireShipState(const platform::Input& i_input) 
	: m_input(i_input), m_isDone(false)
{

}

void ReadyToFireShipState::InitReadyToFire()
{
	m_isDone = false;
}

void ReadyToFireShipState::UpdateReadyToFire(Seconds /*i_deltaTime*/)
{
	const platform::Input::ValueT fireValue = m_input.GetAction(platform::Input::Action::Fire);
	if (fireValue != 0.f)
	{
		m_isDone = true;
	}
}

bool ReadyToFireShipState::IsReadyToFireDone() const
{
	return m_isDone;
}

ShipState<spaceinv::entities::Ship> ReadyToFireShipState::GetFiringState() const
{
	return ShipState<Ship>{
			&Ship::UpdateRecharginFireState,
			&Ship::InitRechargingFireState,
			&Ship::IsRecharginFireDone,
			&Ship::GetReadyToFireState // next state
	};
}

}
}
}