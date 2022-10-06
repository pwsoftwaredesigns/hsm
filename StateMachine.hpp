#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_

#include "_common.hpp"
#include "AbstractState.hpp"
#include <ctti/nameof.hpp>
#include <memory>

//-----[ CLASS: StateMachine ]--------------------------------------------------
template <typename T, typename ROOT>
class StateMachine {
public:
	using visitor_type = typename state_machine_traits<T>::visitor_type;
	using state_machine_type = T;
	
public:
	StateMachine()
	{
		
	}
	
	~StateMachine() 
	{	
		/*
		* Ideally, deinit() needs to be called by T otherwise a substate
		* could access T (via parent()) after it has been destructed.
		*/
		deinit();
	}
	
	//Prevent copy
	StateMachine(const StateMachine&) = delete;
	StateMachine& operator=(const StateMachine&) = delete;
	
public:
	bool dispatch(const AbstractEvent<visitor_type>& e) {
		if (_state) {
			return _state->dispatch(e)();
		} else {
			return false;
		}
	}
	
	void init() {
		_state = std::make_unique<ROOT>(static_cast<T&>(*this));
		if (_state) _state->_init();
	}
	
	void deinit() {
		if (_state) _state->_deinit();
		_state.reset();
	}
	
	name_string_type name() const { return ctti::nameof<T>(); }
	
	name_string_type currentStateName() const { 
		if (_state) return _state->childName();
		else return name();
	}
	
private:
	std::unique_ptr<AbstractState<visitor_type>> _state;
};

#endif //STATEMACHINE_HPP_