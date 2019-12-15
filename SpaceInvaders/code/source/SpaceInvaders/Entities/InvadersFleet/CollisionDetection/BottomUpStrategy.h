#pragma once
#include "../../../Types.h"
#include "../../../../Utils/Types.h"
#include "../../Invader/Invader.h"


namespace spaceinv
{
namespace entities
{
namespace collision_detection
{
template<std::size_t Row, std::size_t Col>
struct BottomUpStrategy
{
	Invader* FindCollingInvader(const Position& i_topLeft, const Position& i_bottomRight)
	{
		for (std::int32_t i = Row - 1; i >= 0; --i)
		{
			for (std::size_t j = 0; j < Col; ++j)
			{
				Invader& invader = m_invadersFleet[i][j];
				const Position& invaderPos = invader.GetPosition();
				const Position::ValueT& invadersRowBottom = invaderPos.GetY() + m_spriteSize.h;
				if (i_topLeft.GetY() > invadersRowBottom)
				{
					return nullptr; // it hasn't reached the whole fleet yet
				}
				else if (i_bottomRight.GetY() >= invaderPos.GetY())
				{
					const Position::ValueT invaderRightMargin = invaderPos.GetX() + m_spriteSize.w;
					if (i_topLeft.GetX() < invaderRightMargin && i_bottomRight.GetX() > invaderPos.GetX())
					{
						if (invader.IsAlive())
						{
							return &invader;
						}
					}
				}
			}
		}
		return nullptr;
	}
//
	Invader(&m_invadersFleet)[Row][Col];
	const utils::Size& m_spriteSize;
};

}
}
}