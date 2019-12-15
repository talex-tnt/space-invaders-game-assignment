#pragma once
#include "Types.h"

#include "GameState.h"
#include "States/IntroGameState.h"
#include "States/ActionPhaseGameState.h"
#include "States/StageClearedGameState.h"
#include "States/GameOverGameState.h"

#include "Scenes/Intro.h"
#include "Scenes/ActionPhase.h"
#include "Scenes/StageCleared.h"
#include "Scenes/GameOver.h"

#include "../Basic/StateMachine.h"

namespace spaceinv
{
class GameContext;

struct GameData
{
	GameData(const GameContext& i_context) 
		: m_intro(i_context)
		, m_actionPhase(i_context)
		, m_stageCleared(i_context)
		, m_gameOver(i_context)
	{}
	scenes::Intro m_intro;
	scenes::ActionPhase m_actionPhase;
	scenes::StageCleared m_stageCleared;
	scenes::GameOver m_gameOver;
};
class Game 
	: private GameData
	, private states::IntroGameState
	, private states::ActionPhaseGameState
	, private states::StageClearedGameState
	, private states::GameOverGameState
{
public:
	Game(const GameContext& i_context);
	void Update(Seconds i_deltaTime);
	void Render() const;
	GameState<Game> GetInitialState() const;

private:
	friend states::IntroGameState;
	friend states::ActionPhaseGameState;
	friend states::StageClearedGameState;
	friend states::GameOverGameState;

	basic::StateMachine<Game, GameState> m_stateMachine;
};
}