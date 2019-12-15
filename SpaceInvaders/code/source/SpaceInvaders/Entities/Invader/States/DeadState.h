#pragma once
#include "../InvaderState.h"
#include "../../../../Graphics/SpriteRenderer.h"

namespace spaceinv
{
namespace entities
{
class Invader;
namespace states
{
class DeadState
{
public:
	DeadState();

	void InitDeadState();
	void RenderDeadState(graphics::SpriteRenderer::Sprite, const Position&) const;
	bool IsDeadStateDone() const;
	InvaderState<Invader> GetAliveState() const;

public:
	DeadState(const DeadState&) = delete;
	DeadState(DeadState&&) = delete;

	DeadState& operator=(const DeadState&) = delete;
	DeadState& operator=(DeadState&&) = delete;

protected:
	~DeadState() = default;

private:
	//
};
}
}
}