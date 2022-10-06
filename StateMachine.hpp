#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_

#include "_common.hpp"

//-----[ CLASS: StateMachine ]--------------------------------------------------
template <typename CTX, typename ROOT>
class StateMachine {
public:
	using visitor_type = typename state_machine_traits<CTX>::visitor_type;
	
public:
	StateMachine()
	{
		_init();
	}
	
	~StateMachine() {
		_deinit();
	}
	
public:
	bool dispatch(const AbstractEvent<visitor_type>& e) {
		if (_state) {
			return _state->dispatch(e)();
		} else {
			return false;
		}
	}
	
private:
	void _init() {
		_state = std::make_unique<ROOT>(static_cast<CTX&>(*this));
		_state->_init();
	}
	
	void _deinit() {
		_state->_deinit();
		_state.reset();
	}
	
private:
	std::unique_ptr<AbstractState<CTX>> _state;
};

#endif //STATEMACHINE_HPP_