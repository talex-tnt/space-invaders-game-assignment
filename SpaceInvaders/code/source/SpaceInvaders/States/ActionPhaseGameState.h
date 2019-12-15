#pragma once
#include "../GameState.h"

namespace spaceinv
{
class Game;
namespace scenes
{
	class ActionPhase;
}
namespace states
{
class ActionPhaseGameState
{
public:
	ActionPhaseGameState(scenes::ActionPhase& i_actionPhaseScene);

	void InitActionPhase();
	void UpdateActionPhase(Seconds i_deltaTime);
	void RenderActionPhase() const;
	bool IsActionPhaseDone() const;
	GameState<Game> GetStateAfterActionPhase() const;

public:
	ActionPhaseGameState(const ActionPhaseGameState&) = delete;
	ActionPhaseGameState(ActionPhaseGameState&&) = delete;

	ActionPhaseGameState& operator=(const ActionPhaseGameState&) = delete;
	ActionPhaseGameState& operator=(ActionPhaseGameState&&) = delete;

protected:
	~ActionPhaseGameState() = default;

private:
	scenes::ActionPhase& m_actionPhaseScene;
};
}
}