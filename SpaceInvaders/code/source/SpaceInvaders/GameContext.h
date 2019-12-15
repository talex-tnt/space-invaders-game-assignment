#pragma once
#include "../Graphics/SpriteRenderer.h"
#include "../Graphics/TextRenderer.h"
#include "../Platform/Display.h"
#include "../Platform/Input.h"

struct Engine;

namespace spaceinv
{
class GameContext
{
public:
	using SpriteRenderer = ::graphics::SpriteRenderer;
	using TextRenderer = ::graphics::TextRenderer;
	using Display = ::platform::Display;
	using Input = ::platform::Input;

public:
	GameContext(const Engine& i_engine)
		: m_spriteRenderer(i_engine), m_textRenderer(i_engine), m_display(), m_input(i_engine)
	{ }

	const SpriteRenderer& GetSpriteRenderer() const { return m_spriteRenderer; }
	const TextRenderer& GetTextRenderer() const { return m_textRenderer; }
	const Display& GetDisplay() const { return m_display; }
	const Input& GetInput() const { return m_input; }

private:
	const SpriteRenderer m_spriteRenderer;
	const TextRenderer m_textRenderer;
	const Display m_display;
	const Input m_input;
};
}
