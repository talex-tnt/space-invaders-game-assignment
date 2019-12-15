#pragma once
#include <xutility>

namespace basic
{

template<typename DelegateT, template<class> class StateT>
class StateMachine final
{
public:
	StateMachine(DelegateT& i_delegate, StateT<DelegateT>&& i_initialState)
		:m_delegate(i_delegate), m_currentState(std::move(i_initialState)) 
	{
		((&m_delegate)->*m_currentState.Init)();
	};
	StateT<DelegateT>& GetCurrentState() 
	{ 
		return m_currentState; 
	}
	const StateT<DelegateT>& GetCurrentState() const 
	{ 
		return m_currentState; 
	}
	void Reset(StateT<DelegateT>&& i_initialState) 
	{ 
		m_currentState = i_initialState; 
		((&m_delegate)->*m_currentState.Init)();
	}
	void CheckCurrentState()
	{
		const StateT<DelegateT>& state = GetCurrentState();
		if (((&m_delegate)->*state.IsDone)())
		{
			m_currentState = ((&m_delegate)->*state.GetNextState)();
			((&m_delegate)->*m_currentState.Init)();
		}
	}

public:
	~StateMachine() = default;

	StateMachine(const StateMachine&) = delete;
	StateMachine(StateMachine&&) = delete;

	StateMachine& operator=(const StateMachine&) = delete;
	StateMachine& operator=(StateMachine&&) = delete;

private:
	DelegateT& m_delegate;
	StateT<DelegateT> m_currentState;
};
}