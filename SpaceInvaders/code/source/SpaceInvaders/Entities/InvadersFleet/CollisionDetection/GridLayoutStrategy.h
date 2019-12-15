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
struct GridLayoutStrategy
{
	Invader* FindCollingInvader(const Position& i_topLeft, const Position& i_bottomRight)
	{
		Invader* result = FindCollingInvader(i_topLeft);
		if (!result)
		{
			result = FindCollingInvader(i_bottomRight);
		}
		return result;
	}


	Invader* FindCollingInvader(const Position& i_point)
	{
		const Invader& topLeftInvader = m_invadersFleet[0][0];
		const Position& topLeftMargin = topLeftInvader.GetPosition();
		const Position bottomRightMargin(
			topLeftMargin.GetX() + m_spriteSize.w * Col,
			topLeftMargin.GetY() + m_spriteSize.h * Row);

		if (i_point.GetX() < topLeftMargin.GetX() || i_point.GetY() < topLeftMargin.GetY())
		{
			return nullptr;
		}
		if (i_point.GetX() > bottomRightMargin.GetX() || i_point.GetY() > bottomRightMargin.GetY())
		{
			return nullptr;
		}

		const float x = (i_point.GetX() - topLeftMargin.GetX()) / m_spriteSize.w;
		const float y = (i_point.GetY() - topLeftMargin.GetY()) / m_spriteSize.h;
		const float xIndex = std::min(std::floor(x), Col - 1.f);
		const float yIndex = std::min(std::floor(y), Row - 1.f);

		Invader& invader = m_invadersFleet[static_cast<std::size_t>(yIndex)][static_cast<std::size_t>(xIndex)];
		return invader.IsAlive() ? &invader : nullptr;
	}



	//
	Invader(&m_invadersFleet)[Row][Col];
	const utils::Size& m_spriteSize;
};

}
}
}