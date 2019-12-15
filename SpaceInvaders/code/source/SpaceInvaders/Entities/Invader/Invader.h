#pragma once
#include "../../Types.h"
#include "../../../Utils/Types.h"
#include "../../../Basic/StateMachine.h"
#include "States/DeadState.h"
#include "States/AliveState.h"

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
class Invader : private states::AliveState, private states::DeadState
{
public:
	Invader(const GameContext& i_context, graphics::SpriteRenderer::Sprite i_sprite);
	void Update(Seconds i_deltaTime);
	void Render() const;
	void SetPosition(const Position& i_pos) { m_position = i_pos; }
	const Position& GetPosition() const { return m_position; }
	Position& GetPosition() { return m_position; }
	void Destroy();
	bool IsAlive() const { return m_isAlive; }
	void ActivateAtPosition(const Position& i_pos);


public:
	Invader(const Invader&) = delete;
	Invader(Invader&&) = delete;

	Invader& operator=(const Invader&) = delete;
	Invader& operator=(Invader&&) = delete;

	friend states::DeadState;
	friend states::AliveState;

private:
	InvaderState<spaceinv::entities::Invader> GetInitialState() const;

private:
	basic::StateMachine<Invader, InvaderState> m_stateMachine;
	Position m_position;
	graphics::SpriteRenderer::Sprite m_sprite;
};

}
}