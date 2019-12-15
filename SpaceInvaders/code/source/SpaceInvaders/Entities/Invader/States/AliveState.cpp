#include "AliveState.h"
#include "../Invader.h"

namespace spaceinv
{
namespace entities
{
namespace states
{

AliveState::AliveState(const graphics::SpriteRenderer& i_renderer) 
	: m_renderer(i_renderer),  m_isAlive(true)
{}

void AliveState::InitAliveState()
{
	m_isAlive = true;
}

void AliveState::RenderAliveState(graphics::SpriteRenderer::Sprite i_sprite, const Position& i_pos) const
{
	m_renderer.Render(i_sprite, i_pos);
}

bool AliveState::IsAliveStateDone() const
{
	return !m_isAlive;
}

InvaderState<spaceinv::entities::Invader> AliveState::GetDeadState() const
{
	return InvaderState<Invader>{
			&Invader::RenderDeadState,
			&Invader::InitDeadState,
			&Invader::IsDeadStateDone,
			&Invader::GetAliveState // next state
	};
}

}
}
}