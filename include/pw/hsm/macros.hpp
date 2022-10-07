#ifndef PW_HSM_MACROS_HPP_
#define PW_HSM_MACROS_HPP_

#include <map.h>
#include "map_p.h"

/**
* @param name_ The name of the state machine
* @param root_ The name of the root state of the machine
* @param ... List of events handled by this state machine in the format
*            ([name](,[type]...))
*/
#define PW_HSM_STATE_MACHINE_TRAITS(name_, root_, ...)\
	class _PW_HSM_STATE_MACHINE_VISITOR(name_);\
	using _##name_##_ROOT = root_;\
	MAP_P(_STATE_MACHINE_EVENT, _PW_HSM_STATE_MACHINE_VISITOR(name_), ##__VA_ARGS__)\
	_STATE_MACHINE_VISITOR(_PW_HSM_STATE_MACHINE_VISITOR(name_), ##__VA_ARGS__);

/**
* @param name_ The name of the state machine
*/	
#define PW_HSM_STATE_MACHINE(name_)\
	class name_ : public ::pw::hsm::StateMachine<name_, _PW_HSM_STATE_MACHINE_VISITOR(name_), _##name_##_ROOT>

/**
* @param sm_ The name of the state machine
* @param name_ The name of the state (class)
* @param parent_ The name of this state's parent state (class)
* @param ... List of child states
*/
#define PW_HSM_STATE(sm_, name_, parent_, ...)\
	class name_:\
		public ::pw::hsm::State<name_, _PW_HSM_STATE_MACHINE_VISITOR(sm_), parent_, ##__VA_ARGS__>

//------------------------------------------------------------------------------

#define _PW_HSM_STATE_MACHINE_VISITOR(name_) _##name_##_VISITOR

#define _EXPAND(x_) _EXPANDX x_
#define _EXPANDX(...) __VA_ARGS__
	
#define _STATE_MACHINE_EVENT(visitor_, x_) _STATE_MACHINE_EVENTX(visitor_, _EXPAND(x_))
#define _STATE_MACHINE_EVENTX(visitor_, name_, ...) _STATE_MACHINE_EVENTY(visitor_, name_, ##__VA_ARGS__)
#define _STATE_MACHINE_EVENTY(visitor_, name_, ...)\
	struct _##name_##_NAME { static const char* value() { return #name_; } };\
	using name_ = ::pw::hsm::Event<_##name_##_NAME, visitor_, ##__VA_ARGS__>;

#define _STATE_MACHINE_VISITOR(name_, ...)\
	class name_ {\
	public:\
		MAP(_STATE_MACHINE_VISITOR_VISIT, ##__VA_ARGS__)\
	}
#define _STATE_MACHINE_VISITOR_VISIT(x_) _STATE_MACHINE_VISITOR_VISITX x_
#define _STATE_MACHINE_VISITOR_VISITX(name_, ...)\
	virtual ::pw::hsm::return_type visit(const name_& e) { return ::pw::hsm::PASS; }

#endif //PW_HSM_MACROS_HPP_