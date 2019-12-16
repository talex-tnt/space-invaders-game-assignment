#pragma  once
#include "../Math/Vec2f.h"

struct SpaceInvadersEngine;

namespace platform
{
class Input
{
public:
	using ValueT = float;
	enum class Action : int
	{
		Fire,
		Left,
		Right,
	};

public:
	ValueT GetAction(Action i_action) const;

public:
	Input(const SpaceInvadersEngine& i_engine);

	Input(const Input&) = delete;
	Input(Input&&) = delete;

	Input& operator=(const Input&) = delete;
	Input& operator=(Input&&) = delete;

private:
	const SpaceInvadersEngine& m_engine;
};
}