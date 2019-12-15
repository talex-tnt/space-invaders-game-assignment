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
class AliveState
{
public:
	AliveState(const graphics::SpriteRenderer& i_renderer);

	void InitAliveState();
	void RenderAliveState(graphics::SpriteRenderer::Sprite, const Position&) const;
	bool IsAliveStateDone() const;
	InvaderState<Invader> GetDeadState() const;

public:
	AliveState(const AliveState&) = delete;
	AliveState(AliveState&&) = delete;

	AliveState& operator=(const AliveState&) = delete;
	AliveState& operator=(AliveState&&) = delete;

protected:
	~AliveState() = default;

private:
	const graphics::SpriteRenderer& m_renderer;

protected:
	bool m_isAlive;

};
}
}
}