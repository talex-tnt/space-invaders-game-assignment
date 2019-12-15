#pragma once
#include "../../Types.h"
#include "../../../Utils/Types.h"

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
class Rocket
{
public:
	Rocket(const GameContext& i_context);
	void Update(Seconds i_deltaTime);
	void Render() const;
	void ActivateAtPosition(Position i_pos) { m_active = true;  m_position = i_pos; }
	bool IsActive() const { return m_active; }
	void Destroy() { m_active = false; }
	Position GetTopLeftMargin() const;
	Position GetBottomRightMargin() const;
	const utils::Size& GetSize() const { return m_size; }
public:
	Rocket(const Rocket&) = delete;
	Rocket(Rocket&&) = delete;

	Rocket& operator=(const Rocket&) = delete;
	Rocket& operator=(Rocket&&) = delete;

private:
	const graphics::SpriteRenderer& m_spriteRenderer;
	const utils::Size m_displaySize;
	const utils::Size m_size;
	Position m_position;
	bool m_active;
};

}
}