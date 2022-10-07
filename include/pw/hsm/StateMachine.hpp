#ifndef PW_HSM_STATEMACHINE_HPP_
#define PW_HSM_STATEMACHINE_HPP_

#include "_common.hpp"
#include "AbstractState.hpp"
#include <ctti/nameof.hpp>
#include <memory>
#if PW_HSM_USE_ETL == 1
	#include <etl/pool.h>
#endif

namespace pw::hsm {

//-----[ CLASS: StateMachine ]--------------------------------------------------
template <typename T, typename VISITOR, typename ROOT>
class StateMachine {
public:
	//using visitor_type = typename state_machine_traits<T>::visitor_type;
	using visitor_type = VISITOR;
	using state_machine_type = T;
	
private:
#if PW_HSM_USE_ETL == 1
	using unique_ptr_type = std::unique_ptr<AbstractState<visitor_type>, std::function<void(AbstractState<visitor_type>*)>>;
#else
	using unique_ptr_type = std::unique_ptr<AbstractState<visitor_type>>;
#endif
	
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
#if PW_HSM_USE_ETL == 1
		auto s = _statePool.create(static_cast<T&>(*this));
		_state = unique_ptr_type{s, [this](AbstractState<visitor_type>* ptr){ _statePool.destroy(ptr); }};
#else
		_state = std::make_unique<ROOT>(static_cast<T&>(*this));
#endif

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
#if PW_HSM_USE_ETL == 1
	etl::pool<ROOT, 1> _statePool;
#endif
	unique_ptr_type _state;
};

} //namespace pw::hsm

#endif //PW_HSM_STATEMACHINE_HPP_