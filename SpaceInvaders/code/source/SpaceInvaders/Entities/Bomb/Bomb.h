#pragma once
#include "../../Types.h"
#include "../../../Utils/Types.h"

namespace graphics
{
class SpriteRenderer;
}

namespace spaceinv
{
class GameContext;
namespace entities
{
class Bomb
{
public:
	Bomb(const GameContext& i_context);
	void Update(Seconds i_deltaTime);
	void Render() const;
	void ActivateAtPosition(Position i_pos) { m_active = true;  m_position = i_pos; }
	bool IsActive() const { return m_active; }
	void Destroy() { m_active = false; }
	Position GetTopLeftMargin() const;
	Position GetBottomRightMargin() const;
	const utils::Size& GetSize() const { return m_size; }

public:
	Bomb(const Bomb&) = delete;
	Bomb(Bomb&&) = delete;

	Bomb& operator=(const Bomb&) = delete;
	Bomb& operator=(Bomb&&) = delete;

private:
	const graphics::SpriteRenderer& m_spriteRenderer;
	const utils::Size m_displaySize;
	const utils::Size m_size;
	Position m_position;
	bool m_active;
};

}
}