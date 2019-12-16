#include "Stopwatch.h"
#include <Game/LegacyEngine/SpaceInvadersEngine.h>

namespace
{
utils::Stopwatch::Seconds GetTime(const SpaceInvadersEngine& i_engine)
{
	return i_engine.GetElapsedSeconds();
}
}

namespace utils
{

Stopwatch::Stopwatch(const SpaceInvadersEngine& i_engine)
	: m_engine(i_engine)
	, m_timestamp(i_engine.GetElapsedSeconds())
{

}

void Stopwatch::Reset()
{
	m_timestamp = m_engine.GetElapsedSeconds();
}

Stopwatch::Seconds Stopwatch::GetElapsed() const
{
	return  m_engine.GetElapsedSeconds() - m_timestamp;
}
}