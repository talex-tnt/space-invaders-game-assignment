#pragma once
#include "../ShipState.h"

namespace spaceinv
{

namespace entities
{
class Ship;
namespace states
{
class RechargingFireState
{
public:
	RechargingFireState();

	void InitRechargingFireState();
	void UpdateRecharginFireState(Seconds i_deltaTime);
	bool IsRecharginFireDone() const;
	ShipState<Ship> GetReadyToFireState() const;

public:
	RechargingFireState(const RechargingFireState&) = delete;
	RechargingFireState(RechargingFireState&&) = delete;

	RechargingFireState& operator=(const RechargingFireState&) = delete;
	RechargingFireState& operator=(RechargingFireState&&) = delete;

protected:
	~RechargingFireState() = default;

protected:
	bool m_fired;
	Seconds m_elapsedTime;
	//
};
}
}
}