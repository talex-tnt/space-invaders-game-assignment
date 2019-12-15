#include "IntroGameState.h"
#include "../Game.h"

namespace spaceinv
{
namespace states
{

IntroGameState::IntroGameState(
	scenes::Intro& i_introScene, 
	const scenes::ActionPhase& i_actionPhaseScene
)
	: m_introScene(i_introScene)
	, m_actionPhaseScene(i_actionPhaseScene)
	, m_isDone(false)
{ }

void IntroGameState::InitIntro()
{

}

void IntroGameState::UpdateIntro(Seconds i_deltaTime)
{
	m_introScene.Update(i_deltaTime);
	m_isDone = m_introScene.IsEnded();
}

void IntroGameState::RenderIntro() const
{
	m_actionPhaseScene.Render();
	m_introScene.Render();
}

bool IntroGameState::IsIntroDone() const
{
	return m_isDone;
}

GameState<Game> IntroGameState::GetActionPhaseState() const
{
	return GameState<Game>{
			&Game::UpdateActionPhase,
			&Game::RenderActionPhase,
			&Game::InitActionPhase,
			&Game::IsActionPhaseDone,
			&Game::GetStateAfterActionPhase // next state
	};
}

}
}