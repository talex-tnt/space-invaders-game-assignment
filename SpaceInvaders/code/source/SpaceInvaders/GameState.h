#pragma once
#include "Types.h"
#include "../Basic/StateBase.h"

namespace spaceinv
{
template<typename DelegateT>
struct GameState : public basic::StateBase<GameState, DelegateT>
{
	using UpdateFun = void (DelegateT::*)(Seconds);
	using RenderFun = void (DelegateT::*)() const;;
#if defined(__clang__)
	using InitFun = typename basic::StateBase<GameState, DelegateT>::InitFun;
	using IsDoneFun = typename basic::StateBase<GameState, DelegateT>::IsDoneFun;
	using GetNextStateFun = typename basic::StateBase<GameState, DelegateT>::GetNextStateFun;
	using StateBase = basic::StateBase<GameState, DelegateT>;
#endif
	GameState(
		UpdateFun u, 
		RenderFun r, 
		InitFun i,
		IsDoneFun d,
		GetNextStateFun g
	) : StateBase(i, d, g), Update(u), Render(r) {}

	UpdateFun Update;
	RenderFun Render;
};
}