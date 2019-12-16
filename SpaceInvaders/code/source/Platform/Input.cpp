#include "Input.h"
#include <Game/LegacyEngine/SpaceInvadersEngine.h>
#include <cmath>
#include <type_traits>

namespace
{
template<class T>
constexpr typename std::underlying_type<T>::type GetValue(const T& i_enum) noexcept
{
	return static_cast<typename std::underlying_type<T>::type>(i_enum);
}
}

namespace platform
{
Input::Input(const SpaceInvadersEngine& i_engine)
	: m_engine(i_engine)
{
}

platform::Input::ValueT Input::GetAction(Action i_action) const
{
	const SpaceInvadersEngine::PlayerInput input = m_engine.GetPlayerInput();
	switch (i_action)
	{
	case Action::Fire: return input.fire;
	case Action::Left: return input.left;
	case Action::Right: return input.right;
	}
	return 0.f;
}
}