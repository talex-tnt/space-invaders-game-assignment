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
class StageCleared
{
public:
	StageCleared(const GameContext& i_context);
	void Init();
	void Update(Seconds i_deltaTime);
	void Render() const;
	bool IsEnded() const;

public:
	StageCleared(const StageCleared&) = delete;
	StageCleared(StageCleared&&) = delete;

	StageCleared& operator=(const StageCleared&) = delete;
	StageCleared& operator=(StageCleared&&) = delete;

private:
	bool IsWaitOver() const;

private:
	const graphics::TextRenderer& m_renderer;
	const platform::Input& m_input;
	Position m_stageClearedMessagePos;
	Position m_replayMessagePos;
	Seconds m_elapsedTime;
};

}
}