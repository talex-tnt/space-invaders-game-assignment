#pragma once
#include "../GameState.h"

namespace spaceinv
{
class Game;
namespace scenes
{
class GameOver;
class ActionPhase;
}

namespace states
{
class GameOverGameState
{
public:
	GameOverGameState(scenes::GameOver& i_gameOverScene, const scenes::ActionPhase& i_actionPhaseScene);

	void InitGameOverState();
	void UpdateGameOverState(Seconds i_deltaTime);
	void RenderGameOverState() const;
	bool IsGameOverStateDone() const;

public:
	GameOverGameState(const GameOverGameState&) = delete;
	GameOverGameState(GameOverGameState&&) = delete;

	GameOverGameState& operator=(const GameOverGameState&) = delete;
	GameOverGameState& operator=(GameOverGameState&&) = delete;

protected:
	~GameOverGameState() = default;

private:
	scenes::GameOver& m_gameOverScene;
	const scenes::ActionPhase& m_actionPhaseScene;

	bool m_isDone;
};

}
}