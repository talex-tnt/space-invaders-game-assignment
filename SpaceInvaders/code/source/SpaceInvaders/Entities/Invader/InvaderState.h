#pragma once
#include "../RenderableState.h"

namespace spaceinv
{
	template<typename DelegateT>
	using InvaderState = RenderableState<DelegateT>;
}