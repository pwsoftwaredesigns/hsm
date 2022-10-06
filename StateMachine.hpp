#ifndef STATEMACHINE_HPP_
#define STATEMACHINE_HPP_

//-----[ CLASS: StateMachine ]--------------------------------------------------
template <typename CTX, typename ROOT>
class StateMachine {
public:
	using ctx_type = CTX;
	using visitor_type = typename ctx_type::visitor_type;
	
public:
	StateMachine(ctx_type& context):
		_context(context)
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
		_state = std::make_unique<ROOT>(_context, *this);
		_state->_init();
	}
	
	void _deinit() {
		_state->_deinit();
		_state.reset();
	}
	
private:
	ctx_type& _context;
	std::unique_ptr<AbstractState<ctx_type>> _state;
};

#endif //STATEMACHINE_HPP_