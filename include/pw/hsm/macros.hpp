#ifndef PW_HSM_MACROS_HPP_
#define PW_HSM_MACROS_HPP_

#include <map.h>
#include "map_p.h"

#define STATE_MACHINE(name_, root_, ...)\
	class _##name_##_VISITOR;\
	MAP_P(_STATE_MACHINE_EVENT, _##name_##_VISITOR, ##__VA_ARGS__)\
	_STATE_MACHINE_VISITOR(_##name_##_VISITOR, ##__VA_ARGS__);\
	class name_ : public ::pw::hsm::StateMachine<name_, _##name_##_VISITOR, root_>



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
	virtual ::pw::hsm::state_return_type visit(const name_& e) { return ::pw::hsm::PASS; }

#endif //PW_HSM_MACROS_HPP_