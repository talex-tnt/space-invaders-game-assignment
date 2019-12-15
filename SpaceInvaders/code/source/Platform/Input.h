#pragma  once
#include "../Math/Vec2f.h"

struct Engine;

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
	Input(const Engine& i_engine);

	Input(const Input&) = delete;
	Input(Input&&) = delete;

	Input& operator=(const Input&) = delete;
	Input& operator=(Input&&) = delete;

private:
	const Engine& m_engine;
};
}