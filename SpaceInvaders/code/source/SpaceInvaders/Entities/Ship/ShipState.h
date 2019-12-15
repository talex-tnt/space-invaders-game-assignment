#pragma once
#include "../UpdatableState.h"

namespace spaceinv
{
template<typename DelegateT>
using ShipState = UpdatableState<DelegateT>;
}
