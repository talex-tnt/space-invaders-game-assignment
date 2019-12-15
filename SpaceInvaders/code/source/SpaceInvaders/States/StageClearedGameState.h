#pragma once
#include "../GameState.h"

namespace spaceinv
{
class Game;
namespace scenes
{
class StageCleared;
class ActionPhase;
}

namespace states
{
class StageClearedGameState
{
public:
	StageClearedGameState(scenes::StageCleared& i_stageClearedScene, scenes::ActionPhase& i_actionPhaseScene);

	void InitStageCleared();
	void UpdateStageCleared(Seconds i_deltaTime);
	void RenderStageCleared() const;
	bool IsStageClearedDone() const;

public:
	StageClearedGameState(const StageClearedGameState&) = delete;
	StageClearedGameState(StageClearedGameState&&) = delete;

	StageClearedGameState& operator=(const StageClearedGameState&) = delete;
	StageClearedGameState& operator=(StageClearedGameState&&) = delete;

protected:
	~StageClearedGameState() = default;

private:
	scenes::StageCleared& m_stageClearedScene;
	scenes::ActionPhase& m_actionPhaseScene;

	bool m_isDone;
};

}
}