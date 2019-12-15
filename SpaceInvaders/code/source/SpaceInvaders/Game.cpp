#include "Game.h"
#include "GameContext.h"
#include <stdlib.h>
#include <time.h>   

namespace spaceinv
{

Game::Game(const GameContext& i_context) 
	: GameData(i_context)
	, states::IntroGameState(m_intro, m_actionPhase)
	, states::ActionPhaseGameState(m_actionPhase)
	, states::StageClearedGameState(m_stageCleared, m_actionPhase)
	, states::GameOverGameState(m_gameOver, m_actionPhase)
	, m_stateMachine(*this, GetInitialState())
{
	srand(static_cast<unsigned int>(time(NULL)));
	m_actionPhase.Init(); // since the intro renders the action phase as well
}

void Game::Update(Seconds i_deltaTime)
{
	m_stateMachine.CheckCurrentState();
	const GameState<Game>& state = m_stateMachine.GetCurrentState();
	(this->*state.Update)(i_deltaTime);
}

void Game::Render() const
{
	const GameState<Game>& state = m_stateMachine.GetCurrentState();
	(this->*state.Render)();
}

GameState<spaceinv::Game> Game::GetInitialState() const
{
	return GetStateAfterActionPhase();
}

}

