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
class GameOver
{
public:
	GameOver(const GameContext& i_context);
	void Init();
	void Update(Seconds i_deltaTime);
	void Render() const;
	bool IsEnded() const;
public:
	GameOver(const GameOver&) = delete;
	GameOver(GameOver&&) = delete;

	GameOver& operator=(const GameOver&) = delete;
	GameOver& operator=(GameOver&&) = delete;

private:
	bool IsWaitOver() const;

private:
	const graphics::TextRenderer& m_renderer;
	const platform::Input& m_input;
	Seconds m_elapsedTime;
	Position m_gameOverMessagePos;
	Position m_replayMessagePos;
};

}
}