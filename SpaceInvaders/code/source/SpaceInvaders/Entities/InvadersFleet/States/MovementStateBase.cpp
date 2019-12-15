#include "MovementStateBase.h"
#include "../InvadersFleet.h"
#include "../../Invader/Invader.h"
#include "../../../GameContext.h"

namespace spaceinv
{
namespace entities
{
namespace states
{

MovementStateBase::MovementStateBase(Invader* i_invaders, float& i_speed, std::size_t i_rowCount, std::size_t i_colCount)
	: m_invaders(i_invaders)
	, m_rowCount(i_rowCount)
	, m_colCount(i_colCount) 
	, m_speedRef(i_speed)
	, m_isDone(false)
{}


const Invader& MovementStateBase::GetFirstInvader() const
{
	return *(m_invaders);
}

const Invader& MovementStateBase::GetLastInvader() const
{
	return  *((m_invaders + (m_rowCount - 1) * m_colCount) + (m_colCount - 1));
}

}
}
}