#include "GameOverGameState.h"
#include "../Game.h"

namespace spaceinv
{
namespace states
{

GameOverGameState::GameOverGameState(
	scenes::GameOver& i_stageGameOverScene,
	const scenes::ActionPhase& i_actionPhaseScene)
	: m_gameOverScene(i_stageGameOverScene)
	, m_actionPhaseScene(i_actionPhaseScene)
	, m_isDone(false)
{ }

void GameOverGameState::InitGameOverState()
{
	m_gameOverScene.Init();
}

void GameOverGameState::UpdateGameOverState(Seconds i_deltaTime)
{
	m_gameOverScene.Update(i_deltaTime);
	m_isDone = m_gameOverScene.IsEnded();
}

void GameOverGameState::RenderGameOverState() const
{
	m_actionPhaseScene.Render();
	m_gameOverScene.Render();
}

bool GameOverGameState::IsGameOverStateDone() const
{
	return m_isDone;
}

}
}