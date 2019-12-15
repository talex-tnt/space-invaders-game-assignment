#pragma once
#include "../Types.h"
#include "../../Utils/Types.h"

namespace platform
{
class Input;
}
namespace graphics
{
class TextRenderer;
}

namespace spaceinv
{
class GameContext;
namespace scenes
{
class Intro
{
public:
	Intro(const GameContext& i_context);
	void Update(Seconds i_deltaTime);
	void Render() const;
	bool IsEnded() const;

public:
	Intro(const Intro&) = delete;
	Intro(Intro&&) = delete;

	Intro& operator=(const Intro&) = delete;
	Intro& operator=(Intro&&) = delete;

private:
	const graphics::TextRenderer& m_renderer;
	const platform::Input& m_input;
	const utils::Size m_textSize;
	Position m_position;
};

}
}