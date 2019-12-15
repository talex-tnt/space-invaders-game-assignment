#pragma once
#include "../Types.h"
#include "../../Basic/StateBase.h"

namespace spaceinv
{
template<typename DelegateT>
struct UpdatableState : public basic::StateBase<UpdatableState, DelegateT>
{
	using UpdateFun = void (DelegateT::*)(Seconds);
#if defined(__clang__)
	using InitFun = typename basic::StateBase<UpdatableState, DelegateT>::InitFun;
	using IsDoneFun = typename basic::StateBase<UpdatableState, DelegateT>::IsDoneFun;
	using GetNextStateFun = typename basic::StateBase<UpdatableState, DelegateT>::GetNextStateFun;
	using StateBase = basic::StateBase<UpdatableState, DelegateT>;
#endif
	UpdatableState(
		UpdateFun u, 
		InitFun i,
		IsDoneFun d,
		GetNextStateFun g
	) : StateBase(i, d, g), Update(u) {}
	UpdateFun Update;
};
}