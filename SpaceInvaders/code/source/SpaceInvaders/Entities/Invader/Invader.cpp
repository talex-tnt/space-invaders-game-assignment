#include "Invader.h"
#include "../../GameContext.h"


namespace spaceinv
{
namespace entities
{

Invader::Invader(const GameContext& i_context, graphics::SpriteRenderer::Sprite i_sprite)
	: states::AliveState(i_context.GetSpriteRenderer())
	, states::DeadState()
	, m_stateMachine(*this, GetInitialState())
	, m_sprite(i_sprite)
{
}

void Invader::Update(Seconds /*i_deltaTime*/)
{
	m_stateMachine.CheckCurrentState();
}

void Invader::Render() const
{
	const InvaderState<Invader>& state = m_stateMachine.GetCurrentState();
	(this->*state.Render)(m_sprite, m_position);
}

InvaderState<spaceinv::entities::Invader> Invader::GetInitialState() const
{
	return GetAliveState();
}

void Invader::Destroy()
{
	m_isAlive = false;
}

void Invader::ActivateAtPosition(const Position& i_pos)
{
	m_isAlive = true; 
	m_position = i_pos;
	m_stateMachine.Reset(GetInitialState());
}

}
}