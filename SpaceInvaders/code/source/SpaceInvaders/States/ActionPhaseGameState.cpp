#include "ActionPhaseGameState.h"
#include "../Game.h"

namespace spaceinv
{
namespace states
{

ActionPhaseGameState::ActionPhaseGameState(
	scenes::ActionPhase& i_actionPhaseScene)
	: m_actionPhaseScene(i_actionPhaseScene)
{ }

void ActionPhaseGameState::InitActionPhase()
{
	m_actionPhaseScene.Init();
}

void ActionPhaseGameState::UpdateActionPhase(Seconds i_deltaTime)
{
	m_actionPhaseScene.Update(i_deltaTime);
}

void ActionPhaseGameState::RenderActionPhase() const
{
	m_actionPhaseScene.Render();
}

bool ActionPhaseGameState::IsActionPhaseDone() const
{
	return 
		m_actionPhaseScene.GetState() == scenes::ActionPhase::GameState::k_cleared ||
		m_actionPhaseScene.GetState() == scenes::ActionPhase::GameState::k_gameover;
}

GameState<spaceinv::Game> ActionPhaseGameState::GetStateAfterActionPhase() const
{
	switch (m_actionPhaseScene.GetState())
	{
	case scenes::ActionPhase::GameState::k_cleared:
		return GameState<Game>{
			&Game::UpdateStageCleared,
				&Game::RenderStageCleared,
				&Game::InitStageCleared,
				&Game::IsStageClearedDone,
				&Game::GetActionPhaseState, // next state
		};
	case scenes::ActionPhase::GameState::k_gameover:
		return GameState<Game>{
			&Game::UpdateGameOverState,
				&Game::RenderGameOverState,
				&Game::InitGameOverState,
				&Game::IsGameOverStateDone,
				&Game::GetActionPhaseState, // next state
		};
	default: break;
	}
	// fallback
	return GameState<Game>{
		&Game::UpdateIntro,
			&Game::RenderIntro,
			&Game::InitIntro,
			&Game::IsIntroDone,
			&Game::GetActionPhaseState, // next state
	};
}

}
}