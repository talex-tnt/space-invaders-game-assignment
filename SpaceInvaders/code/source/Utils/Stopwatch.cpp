#include "Stopwatch.h"
#include "../Engine.h"

namespace
{
utils::Stopwatch::Seconds GetTime(const Engine& i_engine)
{
	return const_cast<Engine*>(&i_engine)->GetElapsedSeconds(); // I would expect this method to be const
}
}

namespace utils
{

Stopwatch::Stopwatch(const Engine& i_engine) 
	: m_engine(i_engine)
	, m_timestamp(GetTime(i_engine))
{

}

void Stopwatch::Reset()
{
	m_timestamp = GetTime(m_engine);
}

Stopwatch::Seconds Stopwatch::GetElapsed() const
{
	return GetTime(m_engine) - m_timestamp;
}
}