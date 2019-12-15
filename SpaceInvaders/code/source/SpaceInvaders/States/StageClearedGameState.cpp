#include "StageClearedGameState.h"
#include "../Game.h"

namespace spaceinv
{
namespace states
{

StageClearedGameState::StageClearedGameState(
	scenes::StageCleared& i_stageClearedScene, 
	scenes::ActionPhase& i_actionPhaseScene
)
	: m_stageClearedScene(i_stageClearedScene)
	, m_actionPhaseScene(i_actionPhaseScene)
	, m_isDone(false)
{ }

void StageClearedGameState::InitStageCleared()
{
	m_stageClearedScene.Init();
}

void StageClearedGameState::UpdateStageCleared(Seconds i_deltaTime)
{
	m_stageClearedScene.Update(i_deltaTime);
	m_actionPhaseScene.Update(i_deltaTime);
	m_isDone = m_stageClearedScene.IsEnded();
}

void StageClearedGameState::RenderStageCleared() const
{
	m_actionPhaseScene.Render();
	m_stageClearedScene.Render();
}

bool StageClearedGameState::IsStageClearedDone() const
{
	return m_isDone;
}

}
}