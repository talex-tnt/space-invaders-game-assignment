#pragma  once

struct SpaceInvadersEngine;

namespace utils
{
class Stopwatch
{
public:
	using Seconds = double;

public:
	Stopwatch(const SpaceInvadersEngine& i_engine);

	void Reset();
	Seconds GetElapsed() const;

private:
	const SpaceInvadersEngine& m_engine;
	Seconds m_timestamp;
};
}