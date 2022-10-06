#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_

#include "_common.hpp"

//-----[ CLASS: StateMachine ]--------------------------------------------------
template <typename CTX, typename ROOT>
class StateMachine {
public:
	using visitor_type = typename state_machine_traits<CTX>::visitor_type;
	using state_machine_type = CTX;
	
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
		_state = std::make_unique<ROOT>(static_cast<CTX&>(*this));
		_state->_init();
	}
	
	void deinit() {
		_state->_deinit();
		_state.reset();
	}
	
private:
	std::unique_ptr<AbstractState<visitor_type>> _state;
};

#endif //STATEMACHINE_HPP_