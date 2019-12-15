#include "Input.h"
#include "../Engine.h"
#include <cmath>
#include <type_traits>

namespace
{
Engine& GetEngine(const Engine& i_engine)
{
	return *const_cast<Engine*>(&i_engine); // #todo: ask why some engine's methods are not const qualified
}
template<class T>
constexpr typename std::underlying_type<T>::type GetValue(const T& i_enum) noexcept
{
	return static_cast<typename std::underlying_type<T>::type>(i_enum);
}
}

namespace platform
{
Input::Input(const Engine& i_engine)
	: m_engine(i_engine)
{
}

platform::Input::ValueT Input::GetAction(Action i_action) const
{
	const Engine::PlayerInput input = GetEngine(m_engine).GetPlayerInput();
	switch (i_action)
	{
	case Action::Fire: return input.fire;
	case Action::Left: return input.left;
	case Action::Right: return input.right;
	}
	return 0.f;
}
}