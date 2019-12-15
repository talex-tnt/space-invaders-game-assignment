#pragma once
#include "../../Types.h"
#include "../../../Utils/Types.h"
#include "../../../Basic/StateMachine.h"
#include "../Invader/Invader.h"
#include "../Bomb/Bomb.h"

#include "States/HorizontalMovementState.h"
#include "States/VerticalMovementState.h"
#include "BombDelegate.h"
#include "CollisionDetection/BottomUpStrategy.h"
#include "CollisionDetection/GridLayoutStrategy.h"

namespace graphics
{
class SpriteRenderer;
}

namespace spaceinv
{
class GameContext;
namespace entities
{
class Rocket;
struct InvadersFleetData
{
	InvadersFleetData(const GameContext& i_context);
	constexpr static std::size_t k_invadersRowCount = 5;
	constexpr static std::size_t k_invadersColCount = 10;
	constexpr static float k_initialSpeed = 45.f;

	Invader m_invadersFleet[k_invadersRowCount][k_invadersColCount]; //that's all we have, std::array throws exeptions..
	float m_speed;
};

class InvadersFleet 
	: private InvadersFleetData
	, private states::HorizontalMovementState
	, private states::VerticalMovementState
{
public:
	using SpriteSize = graphics::SpriteSize;
	using SpriteRenderer = graphics::SpriteRenderer;
	using CollisionDetectionStrategy = collision_detection::BottomUpStrategy<InvadersFleetData::k_invadersRowCount, InvadersFleetData::k_invadersColCount>;
	using CollisionDetectionStrategyGrid = collision_detection::GridLayoutStrategy<InvadersFleetData::k_invadersRowCount, InvadersFleetData::k_invadersColCount>;

	InvadersFleet(const GameContext& i_context);
	void InitFleet();
	void Update(Seconds i_deltaTime);
	void Render() const;
	bool CheckCollision(const Rocket& i_rocket);
	bool CheckCollision(const Position& i_pos, const SpriteSize& i_size);

	std::size_t GetActiveFleetSize() const { return m_activeInvaderCount; }
	bool IsInvasionSucceded() const { return m_invasionSucceded; }

public:
	InvadersFleet(const InvadersFleet&) = delete;
	InvadersFleet(InvadersFleet&&) = delete;

	InvadersFleet& operator=(const InvadersFleet&) = delete;
	InvadersFleet& operator=(InvadersFleet&&) = delete;

	friend states::HorizontalMovementState;
	friend states::VerticalMovementState;

private:
	void InitFirstVerticalMovementState();
	InvadersFleetState<spaceinv::entities::InvadersFleet> GetInitialState() const;
	void UpdateFleet(Seconds i_deltaTime);
	void UpdateBombs(Seconds i_deltaTime);
	Position::ValueT GetFleetHeight() const;
	void UpdateStateMachine(Seconds i_deltaTime);
	bool HasInvasionSucceeded(const Invader& i_invader) const;

private:
	basic::StateMachine<InvadersFleet, InvadersFleetState> m_stateMachine;
	const utils::Size m_spriteSize;
	Position::ValueT m_fleetHeight;
	BombDelegate m_bombDelegate;
	//CollisionDetectionStrategy m_collisionDetectionStrategy;
	CollisionDetectionStrategyGrid m_collisionDetectionStrategy;
	std::size_t m_activeInvaderCount;
	Position::ValueT m_invasionVerticalTarget;
	bool m_invasionSucceded;
};

}
}