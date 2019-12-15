#pragma once
#include "../../Types.h"
#include "../../../Utils/Types.h"
#include "../Bomb/Bomb.h"
#include "../Invader/Invader.h"


namespace spaceinv
{
class GameContext;
namespace entities
{

class BombDelegate 
{
public:
	BombDelegate(const GameContext& i_context);
	
	void Init();
	void Update(Seconds i_deltaTime);
	void Render() const;

	template<std::size_t Row, std::size_t Col>
	void DropBombs(Invader(&i_invaders)[Row][Col], const utils::Size& i_spriteSize);
	bool CheckCollisions(const Position& i_topLeft, const Position& i_bottomRight);
	
public:
	BombDelegate(const BombDelegate&) = delete;
	BombDelegate(BombDelegate&&) = delete;

	BombDelegate& operator=(const BombDelegate&) = delete;
	BombDelegate& operator=(BombDelegate&&) = delete;

private:
	void DropBombAtPosition(const Position& i_pos);
	bool CanDropBomb() const;
	Seconds GetRandomWaitTime() const;
	std::size_t GetNextCandidateIndex(std::size_t i_count) const;

private:
	constexpr static std::size_t k_invadersBombCount = 3;
	Bomb m_bombs[k_invadersBombCount];
	Seconds m_timeElaspedSinceLastBombDrop;
	Seconds m_waitTime;
};

}
}

namespace spaceinv
{
namespace entities
{
	template<std::size_t Row, std::size_t Col>
	inline void BombDelegate::DropBombs(Invader(&i_invaders)[Row][Col], const utils::Size& i_spriteSize)
	{
		const bool canDropBomb = CanDropBomb();
		const std::size_t invaderIndexCandidate = GetNextCandidateIndex(Row);
		std::size_t activeInvaderIndex = 0u;
		if (canDropBomb)
		{
			for (std::size_t i = 0; i < Col; ++i) //left to right
			{
				for (std::int32_t j = Row - 1; j >= 0; --j) // bottom to top
				{
					const Invader& invader = i_invaders[j][i];
					if (invader.IsAlive())
					{
						if (activeInvaderIndex == invaderIndexCandidate)
						{
							Position pos = invader.GetPosition();
							pos.GetY() += i_spriteSize.h / 2;
							DropBombAtPosition(pos);
							return;
						}
						j = -1;
						++activeInvaderIndex;
					}
				}
			}
		}
	}
}
}