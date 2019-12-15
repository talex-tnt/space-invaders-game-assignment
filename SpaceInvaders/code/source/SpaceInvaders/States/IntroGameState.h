#pragma once
#include "../GameState.h"

namespace spaceinv
{
class Game;
namespace scenes
{
class Intro;
class ActionPhase;
}

namespace states
{
class IntroGameState
{
public:
	IntroGameState(scenes::Intro& i_introScene, const scenes::ActionPhase& i_actionPhaseScene);

	void InitIntro();
	void UpdateIntro(Seconds i_deltaTime);
	void RenderIntro() const;
	bool IsIntroDone() const;
	GameState<Game> GetActionPhaseState() const;

public:
	IntroGameState(const IntroGameState&) = delete;
	IntroGameState(IntroGameState&&) = delete;

	IntroGameState& operator=(const IntroGameState&) = delete;
	IntroGameState& operator=(IntroGameState&&) = delete;

protected:
	~IntroGameState() = default;

private:
	scenes::Intro& m_introScene;
	const scenes::ActionPhase& m_actionPhaseScene;
	bool m_isDone;
};

}
}