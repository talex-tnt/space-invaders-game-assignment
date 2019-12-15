#pragma once

namespace basic
{
// basic interface for the StateMachine
//
template<template<class> class DerivedStateT, typename DelegateT>
struct StateBase
{
	using InitFun = void (DelegateT::*)();
	using IsDoneFun = bool (DelegateT::*)() const;
	using GetNextStateFun = DerivedStateT<DelegateT>(DelegateT::*)() const;

	StateBase(InitFun i, IsDoneFun d, GetNextStateFun g)
		: Init(i), IsDone(d), GetNextState(g) {}
	InitFun Init;
	IsDoneFun IsDone;
	GetNextStateFun GetNextState;

protected:
	~StateBase() = default;
};
}