#ifndef MACROS_HPP_
#define MACROS_HPP_

#include <map.h>
#include "map_p.h"

#define STATE_MACHINE(name_, root_, ...)\
	class _##name_##_VISITOR;\
	MAP_P(_STATE_MACHINE_EVENT, _##name_##_VISITOR, ##__VA_ARGS__)\
	_STATE_MACHINE_VISITOR(_##name_##_VISITOR, ##__VA_ARGS__);\
	_STATE_MACHINE_TRAITS(name_, _##name_##_VISITOR);\
	class name_ : public StateMachine<name_, root_>



#define _EXPAND(x_) _EXPANDX x_
#define _EXPANDX(...) __VA_ARGS__
	
#define _STATE_MACHINE_EVENT(visitor_, x_) _STATE_MACHINE_EVENTX(visitor_, _EXPAND(x_))
#define _STATE_MACHINE_EVENTX(visitor_, name_, ...) _STATE_MACHINE_EVENTY(visitor_, name_, ##__VA_ARGS__)
#define _STATE_MACHINE_EVENTY(visitor_, name_, ...)\
	struct _##name_##_NAME { static const char* value() { return #name_; } };\
	using name_ = Event<_##name_##_NAME, visitor_, ##__VA_ARGS__>;

#define _STATE_MACHINE_VISITOR(name_, ...)\
	class name_ {\
	public:\
		MAP(_STATE_MACHINE_VISITOR_VISIT, ##__VA_ARGS__)\
	}
#define _STATE_MACHINE_VISITOR_VISIT(x_) _STATE_MACHINE_VISITOR_VISITX x_
#define _STATE_MACHINE_VISITOR_VISITX(name_, ...)\
	virtual state_return_type visit(const name_& e) { return PASS; }
	
	
#define _STATE_MACHINE_TRAITS(name_, visitor_)\
	template<>\
	struct state_machine_traits<name_> {\
		using visitor_type = visitor_;\
	}

#endif //MACROS_HPP_