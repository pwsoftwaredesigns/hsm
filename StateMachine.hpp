#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_

#include "_common.hpp"

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
	
	~StateMachine() {
		
	}
	
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
		_state->_init();
	}
	
	void deinit() {
		_state->_deinit();
		_state.reset();
	}
	
	ctti::detail::cstring name() const { return ctti::nameof<T>(); }
	
	ctti::detail::cstring currentStateName() const { 
		if (_state) return _state->childName();
		else return name();
	}
	
private:
	std::unique_ptr<AbstractState<visitor_type>> _state;
};

#endif //STATEMACHINE_HPP_