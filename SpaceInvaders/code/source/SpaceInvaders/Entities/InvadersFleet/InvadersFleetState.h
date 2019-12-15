#pragma once
#include "../UpdatableState.h"

namespace spaceinv
{
	template<typename DelegateT>
	using InvadersFleetState = UpdatableState<DelegateT>;
}