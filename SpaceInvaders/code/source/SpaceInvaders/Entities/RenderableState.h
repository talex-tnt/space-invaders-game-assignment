#pragma once
#include "../Types.h"
#include "../../Basic/StateBase.h"
#include "../../Graphics/SpriteRenderer.h"

namespace spaceinv
{
template<typename DelegateT>
struct RenderableState : public basic::StateBase<RenderableState, DelegateT>
{
	using RenderFun = void (DelegateT::*)(graphics::SpriteRenderer::Sprite, const Position&) const;;
#if defined(__clang__)
	using InitFun = typename basic::StateBase<RenderableState, DelegateT>::InitFun;
	using IsDoneFun = typename basic::StateBase<RenderableState, DelegateT>::IsDoneFun;
	using GetNextStateFun = typename basic::StateBase<RenderableState, DelegateT>::GetNextStateFun;
	using StateBase = basic::StateBase<RenderableState, DelegateT>;
#endif
	RenderableState(
		RenderFun r, 
		InitFun i,
		IsDoneFun d,
		GetNextStateFun g
	) : StateBase(i, d, g), Render(r) {}
	RenderFun Render;
};
}