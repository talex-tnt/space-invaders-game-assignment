#include "BombDelegate.h"
#include "../../GameContext.h"

#include <assert.h>
#include <stdlib.h>

namespace spaceinv
{
namespace entities
{
namespace
{
static const Seconds k_bombDropMaxTimeInterval(1);
static const Seconds k_bombDropMinTimeInterval(0.25);
//
bool CheckBombCollision(const Bomb& i_bomb, const Position& i_topLeft, const Position& i_bottomRight);
}

BombDelegate::BombDelegate(const GameContext& i_context)
	: m_bombs{
			{i_context},
			{i_context},
			{i_context},
}
, m_timeElaspedSinceLastBombDrop(0.f)
, m_waitTime(GetRandomWaitTime())
{ 
}

void BombDelegate::Init()
{
	for (std::size_t i = 0; i < k_invadersBombCount; ++i)
	{
		m_bombs[i].Destroy();
	}
	m_timeElaspedSinceLastBombDrop = 0;
}

void BombDelegate::Update(Seconds i_deltaTime)
{
	for (std::size_t i = 0; i < k_invadersBombCount; ++i)
	{
		Bomb& bomb = m_bombs[i];
		bomb.Update(i_deltaTime);
	}
	m_timeElaspedSinceLastBombDrop += i_deltaTime;
}

void BombDelegate::DropBombAtPosition(const Position& i_pos)
{
	for (std::size_t i = 0; i < k_invadersBombCount; ++i)
	{
		 Bomb& bomb = m_bombs[i];
		if (!bomb.IsActive())
		{
			bomb.ActivateAtPosition(i_pos);
			break;
		}
	}
	m_timeElaspedSinceLastBombDrop = 0;
	m_waitTime = GetRandomWaitTime();
}

bool BombDelegate::CanDropBomb() const
{
	return m_timeElaspedSinceLastBombDrop > m_waitTime;
}

Seconds BombDelegate::GetRandomWaitTime() const 
{
	const int ms = (static_cast<int>(k_bombDropMaxTimeInterval) * 1000);
	const Seconds randWait = (rand() % ms) / 1000.f;
	const Seconds waitTime = k_bombDropMinTimeInterval + randWait;
	return waitTime;
}

std::size_t BombDelegate::GetNextCandidateIndex(std::size_t i_count) const
{
	return rand() % i_count;
}

bool BombDelegate::CheckCollisions(const Position& i_topLeft, const Position& i_bottomRight)
{
	for (std::size_t i = 0; i < k_invadersBombCount; ++i)
	{
		Bomb& bomb = m_bombs[i];
		const bool collided = CheckBombCollision(bomb, i_topLeft, i_bottomRight);
		if (collided) 
		{
			bomb.Destroy();
			return true;
		}
	}
	return false;
}
namespace 
{
bool CheckBombCollision(const Bomb& i_bomb, const Position& i_topLeft, const Position& i_bottomRight)
{
	return i_bomb.IsActive() &&
		i_topLeft.GetX() < i_bomb.GetBottomRightMargin().GetX() &&
		i_bottomRight.GetX() > i_bomb.GetTopLeftMargin().GetX() &&
		i_topLeft.GetY() < i_bomb.GetBottomRightMargin().GetY() &&
		i_bottomRight.GetY() > i_bomb.GetTopLeftMargin().GetY();
}
}

void BombDelegate::Render() const
{
	for (std::size_t i = 0; i < k_invadersBombCount; ++i)
	{
		const Bomb& bomb = m_bombs[i];
		bomb.Render();
	}
}

}
}