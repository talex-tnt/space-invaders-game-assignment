#include "ActionPhase.h"
#include "../GameContext.h"

#include <cmath>
#include <assert.h>

namespace spaceinv
{
namespace scenes
{
namespace
{
static const ActionPhase::ScoreT k_invaderDestroyedScore = 100u;
static const ActionPhase::LivesT k_initialLives = 3u;
static const ActionPhase::LivesT k_maxFleetCount = 3u;
}

ActionPhase::ActionPhase(const GameContext& i_context)
	: m_textRenderer(i_context.GetTextRenderer())
	, m_spriteRenderer(i_context.GetSpriteRenderer())
	, m_displaySize(i_context.GetDisplay().GetSize())
	, m_ship(i_context)
	, m_invaders(i_context)
	, m_rocket(i_context)
	, m_scoreTextPos(0.f, 0.f)
	, m_score(0u)
	, m_lives(k_initialLives)
	, m_fleetCount(k_maxFleetCount)
	, m_gameState(GameState::k_idle)
{
}

void ActionPhase::Init()
{
	m_gameState = GameState::k_playing;
	m_score = 0u;
	m_lives = k_initialLives;
	m_invaders.InitFleet();
}

void ActionPhase::Update(Seconds i_deltaTime)
{
	m_ship.Update(i_deltaTime);
	UpdateRocket(i_deltaTime);
	m_invaders.Update(i_deltaTime);
	UpdateGameState();
}

void ActionPhase::UpdateRocket(Seconds i_deltaTime)
{
	entities::Rocket* rocket = FindInactiveRocket();
	if (rocket && m_ship.CheckFireStatus())
	{
		m_rocket.ActivateAtPosition(m_ship.GetPosition());
	}
	m_rocket.Update(i_deltaTime);
}

void ActionPhase::UpdateGameState()
{
	if (m_lives == 0u)
	{
		m_gameState = GameState::k_gameover;
	}
	else if (
		m_invaders.IsInvasionSucceded() || 
		m_invaders.CheckCollision(m_ship.GetPosition(), m_ship.GetSpriteSize()))
	{
		assert(m_lives > 0u); // #fixme: use some debug assert
		m_lives--;
	} 
	else if (m_rocket.IsActive())
	{
		if (m_invaders.CheckCollision(m_rocket))
		{
			m_rocket.Destroy();
			m_score += k_invaderDestroyedScore;
			if (m_invaders.GetActiveFleetSize() == 0u)
			{
				if (m_fleetCount == 0u)
				{
					m_gameState = GameState::k_cleared;
				}
				else 
				{
					--m_fleetCount;
					m_invaders.InitFleet();
				}
			} 
		}
	}
}

entities::Rocket* ActionPhase::FindInactiveRocket() // there's only 1 rocket for now..
{
	return !m_rocket.IsActive() ? &m_rocket : nullptr;
}

void ActionPhase::Render() const
{
	m_ship.Render();
	m_invaders.Render();
	m_rocket.Render();
	m_textRenderer.Render("Score: %ld", m_score, m_scoreTextPos);
	RenderLives();
}

void ActionPhase::RenderLives() const
{
	const Position::ValueT shipWidth = static_cast<Position::ValueT>(m_ship.GetSpriteSize().w);
	Position pos(m_displaySize.w - shipWidth, 0.f);
	for (int i = static_cast<int>(m_lives) - 1; i >= 0; --i)
	{
		m_spriteRenderer.Render(graphics::SpriteRenderer::Sprite::Player, pos);
		pos.GetX() -= shipWidth;
	}
}
}
}