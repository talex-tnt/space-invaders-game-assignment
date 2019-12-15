#include "InvadersFleet.h"
#include "../../GameContext.h"
#include "../Rocket/Rocket.h"

#include <cmath>
#include <algorithm>
#include <assert.h>
#include <stdlib.h>

namespace spaceinv
{
namespace entities
{

using Sprite = graphics::SpriteRenderer::Sprite;

InvadersFleet::InvadersFleet(const GameContext& i_context)
	: InvadersFleetData(i_context)
	, states::HorizontalMovementState(i_context, &m_invadersFleet[0][0], m_speed, k_invadersRowCount, k_invadersColCount)
	, states::VerticalMovementState(i_context, &m_invadersFleet[0][0], m_speed, k_invadersRowCount, k_invadersColCount)
	, m_stateMachine(*this, GetInitialState())
	, m_spriteSize(i_context.GetSpriteRenderer().GetSpriteSize())
	, m_bombDelegate(i_context)
	, m_collisionDetectionStrategy{ m_invadersFleet, m_spriteSize }
	, m_invasionVerticalTarget(static_cast<Position::ValueT>(i_context.GetDisplay().GetSize().h))
	, m_invasionSucceded(false)
{ 
	InitFleet();
}

void InvadersFleet::InitFleet()
{
	// #todo
	// I'm realizing now, after reviewing the README.md, that it states:
	// The aliens start out at the top left corner of the screen,
	// I changed that in one of my latest refactors..

	Position pos;
	Position::ValueT xPos = (k_invadersColCount* m_spriteSize.w) / 2.f;
	pos.GetX() += xPos;
	pos.GetY() -= GetFleetHeight();

	for (std::size_t i = 0; i < k_invadersRowCount; ++i)
	{
		for (std::size_t j = 0; j < k_invadersColCount; ++j)
		{
			m_invadersFleet[i][j].ActivateAtPosition(pos);
			pos.SetX(pos.GetX() + m_spriteSize.w);
		}
		pos.SetY(pos.GetY() + m_spriteSize.h);
		pos.SetX(xPos);
	}

	m_bombDelegate.Init();
	m_activeInvaderCount = k_invadersRowCount * k_invadersColCount;
	m_stateMachine.Reset(GetInitialState());
	m_speed = k_initialSpeed;
	m_invasionSucceded = false;
}

spaceinv::Position::ValueT InvadersFleet::GetFleetHeight() const
{
	return k_invadersRowCount * static_cast<spaceinv::Position::ValueT>(m_spriteSize.h) + m_spriteSize.h;
}

void InvadersFleet::Update(Seconds i_deltaTime)
{
	UpdateStateMachine(i_deltaTime);
	UpdateFleet(i_deltaTime);
	UpdateBombs(i_deltaTime);
}

void InvadersFleet::UpdateStateMachine(Seconds i_deltaTime)
{
	m_stateMachine.CheckCurrentState();
	const InvadersFleetState<InvadersFleet>& state = m_stateMachine.GetCurrentState();
	(this->*state.Update)(i_deltaTime);
}

bool InvadersFleet::HasInvasionSucceeded(const Invader& i_invader) const
{
	if (i_invader.IsAlive())
	{
		const Position::ValueT& invadersRowBottom = i_invader.GetPosition().GetY() + m_spriteSize.h;
		if (invadersRowBottom >= m_invasionVerticalTarget)
		{
			return true;
		}
	}
	return false;
}

void InvadersFleet::UpdateFleet(Seconds i_deltaTime)
{
	for (std::int32_t i = k_invadersRowCount - 1; i >= 0; --i)
	{
		for (std::size_t j = 0; j < k_invadersColCount; ++j)
		{
			Invader& invader = m_invadersFleet[i][j];
			invader.Update(i_deltaTime);
			if (HasInvasionSucceeded(invader))
			{
				m_invasionSucceded = true;
			}
		}
	}
}

void InvadersFleet::UpdateBombs(Seconds i_deltaTime)
{
	m_bombDelegate.Update(i_deltaTime);
	m_bombDelegate.DropBombs(m_invadersFleet, m_spriteSize);
}

bool InvadersFleet::CheckCollision(const Rocket& i_rocket)
{
	const Position& rocketTopLeft = i_rocket.GetTopLeftMargin();
	const Position&  rocketBottomRight = i_rocket.GetBottomRightMargin();
	if (Invader* invaderPtr = m_collisionDetectionStrategy.FindCollingInvader(rocketTopLeft, rocketBottomRight))
	{
		invaderPtr->Destroy();
		assert(m_activeInvaderCount > 0u); // #fixme: use some debug assert
		if (m_activeInvaderCount > 0u) {
			m_activeInvaderCount--;
		}
		// we hit only 1 invader at the time even though
		// the rocket might collide with multiple invaders
		return true;
	}
	return false;
}

bool InvadersFleet::CheckCollision(const Position& i_pos, const SpriteSize& i_size)
{
	const Position& shipTopLeft = i_pos;
	const Position  shipBottomRight(i_pos.GetX() + i_size.w, i_pos.GetY()+ i_size.h);
	const bool result = m_collisionDetectionStrategy.FindCollingInvader(shipTopLeft, shipBottomRight) != nullptr;
	if (!result) {
		return m_bombDelegate.CheckCollisions(shipTopLeft, shipBottomRight);
	}
	return result;
}

void InvadersFleet::Render() const
{
	m_bombDelegate.Render();
	for (std::size_t i = 0; i < k_invadersRowCount; ++i)
	{
		for (std::size_t j = 0; j < k_invadersColCount; ++j)
		{
			m_invadersFleet[i][j].Render();
		}
	}
}

void InvadersFleet::InitFirstVerticalMovementState()
{
	InitVerticalMovementState();
	m_maxVerticalShift = GetFleetHeight() + m_spriteSize.h;
}

InvadersFleetState<spaceinv::entities::InvadersFleet> InvadersFleet::GetInitialState() const
{
	return InvadersFleetState<InvadersFleet>{
			&InvadersFleet::UpdateVerticalMovementState,
			&InvadersFleet::InitFirstVerticalMovementState,
			&InvadersFleet::IsVerticalMovementDone,
			&InvadersFleet::GetHorizontalMovementState // next state
	};
}

InvadersFleetData::InvadersFleetData(const GameContext& i_context)
	: m_invadersFleet{
		{
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1}
		}, {
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2}
		}, {
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1}
		}, {
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1},
			{i_context, Sprite::Enemy1}
		}, {
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2},
			{i_context, Sprite::Enemy2}
		}
	}
	, m_speed(k_initialSpeed)
{ }

}
}