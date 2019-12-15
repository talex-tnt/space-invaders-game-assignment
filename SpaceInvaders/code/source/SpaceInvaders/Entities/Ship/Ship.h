#pragma once
#include "../../Types.h"
#include "../../../Utils/Types.h"
#include "../../../Basic/StateMachine.h"
#include "States/ReadyToFireShipState.h"
#include "States/RechargingFireState.h"

namespace platform
{
class Input;
}
namespace graphics
{
class SpriteRenderer;
}

namespace spaceinv
{
class GameContext;
namespace entities
{
class Ship : private states::ReadyToFireShipState, private states::RechargingFireState
{
public:
	Ship(const GameContext& i_context);
	void Update(Seconds i_deltaTime);
	void Render() const;
	bool CheckFireStatus();
	const Position& GetPosition() const { return m_position; }
	const utils::Size& GetSpriteSize() const { return m_spriteSize; }

public:
	Ship(const Ship&) = delete;
	Ship(Ship&&) = delete;

	Ship& operator=(const Ship&) = delete;
	Ship& operator=(Ship&&) = delete;

	friend states::ReadyToFireShipState;
	friend states::RechargingFireState;

private:
	ShipState<spaceinv::entities::Ship> GetInitialState() const;
	void Move(Seconds i_deltaTime);

private:
	const graphics::SpriteRenderer& m_spriteRenderer;
	const platform::Input& m_input;
	const utils::Size m_displaySize;
	const Position::ValueT m_minX;
	const Position::ValueT m_maxX;
	Position m_position;
	const utils::Size m_spriteSize;
	basic::StateMachine<Ship, ShipState> m_stateMachine;
};

}
}