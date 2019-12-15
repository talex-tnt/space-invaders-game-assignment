#pragma once
#include "../ShipState.h"

namespace platform
{
	class Input;
}

namespace spaceinv
{

namespace entities
{
class Ship;
namespace states
{
class ReadyToFireShipState
{
public:
	ReadyToFireShipState(const platform::Input& i_input);

	void InitReadyToFire();
	void UpdateReadyToFire(Seconds i_deltaTime);
	bool IsReadyToFireDone() const;
	ShipState<Ship> GetFiringState() const;

public:
	ReadyToFireShipState(const ReadyToFireShipState&) = delete;
	ReadyToFireShipState(ReadyToFireShipState&&) = delete;

	ReadyToFireShipState& operator=(const ReadyToFireShipState&) = delete;
	ReadyToFireShipState& operator=(ReadyToFireShipState&&) = delete;

protected:
	~ReadyToFireShipState() = default;

private:
	const platform::Input& m_input;

protected:
	bool m_isDone;
};
}
}
}