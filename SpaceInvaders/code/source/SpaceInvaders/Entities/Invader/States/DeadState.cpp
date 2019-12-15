#include "DeadState.h"
#include "../Invader.h"

namespace spaceinv
{
namespace entities
{
namespace states
{
DeadState::DeadState() = default;

void DeadState::InitDeadState()
{
}

void DeadState::RenderDeadState(graphics::SpriteRenderer::Sprite, const Position&) const
{
}

bool DeadState::IsDeadStateDone() const
{
	return false;
}

InvaderState<spaceinv::entities::Invader> DeadState::GetAliveState() const
{
	return InvaderState<Invader>{
			&Invader::RenderAliveState,
			&Invader::InitAliveState,
			&Invader::IsAliveStateDone,
			&Invader::GetDeadState // next state
	};
}

}
}
}