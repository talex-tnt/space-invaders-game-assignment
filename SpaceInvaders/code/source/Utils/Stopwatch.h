#pragma  once

struct Engine;

namespace utils
{
class Stopwatch
{
public:
	using Seconds = double;

public:
	Stopwatch(const Engine& i_engine);

	void Reset();
	Seconds GetElapsed() const;

private:
	const Engine& m_engine;
	Seconds m_timestamp;
};
}