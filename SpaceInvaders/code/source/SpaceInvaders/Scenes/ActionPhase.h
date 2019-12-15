#pragma once
#include "../Types.h"
#include "../../Utils/Types.h"
#include "../Entities/Ship/Ship.h"
#include "../Entities/InvadersFleet/InvadersFleet.h"
#include "../Entities/Rocket/Rocket.h"

namespace graphics
{
class TextRenderer;
class SpriteRenderer;
}

namespace spaceinv
{
class GameContext;
namespace scenes
{
class ActionPhase
{
public:
	ActionPhase(const GameContext& i_context);
	void Init();
	void Update(Seconds i_deltaTime);
	void Render() const;

	enum class GameState
	{
		k_idle, k_playing, k_gameover, k_cleared
	};

	GameState GetState() const { return m_gameState; }

public:
	ActionPhase(const ActionPhase&) = delete;
	ActionPhase(ActionPhase&&) = delete;

	ActionPhase& operator=(const ActionPhase&) = delete;
	ActionPhase& operator=(ActionPhase&&) = delete;

	void UpdateRocket(Seconds i_deltaTime);
	void UpdateGameState();
	entities::Rocket* FindInactiveRocket();

private:
	void RenderLives() const;

public:
	using ScoreT = std::size_t;
	using LivesT = std::size_t;

private:
	const graphics::TextRenderer& m_textRenderer;
	const graphics::SpriteRenderer& m_spriteRenderer;
	const utils::Size m_displaySize;
	entities::Ship m_ship;
	entities::InvadersFleet m_invaders;
	entities::Rocket m_rocket;
	const Position m_scoreTextPos;
	ScoreT m_score;
	LivesT m_lives;
	std::size_t m_fleetCount;

	GameState m_gameState;
};

}
}