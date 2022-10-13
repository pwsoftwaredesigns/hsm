#ifndef PW_HSM_MACROS_HPP_
#define PW_HSM_MACROS_HPP_

#ifndef __GNUC__
#error "GNU extensions must be availabel for ##__VA_ARGS__ to work"
#endif

#include <pw/macros/map.h>

/**
* @brief Declare an event type
*
* @param sm_ The name of the state machine
* @param name_ The name of the event
* @param ... List of type-name pairs of arguments for the event in the form
*            ([type], [name]), ...
*/
#define PW_HSM_EVENT(sm_, name_, ...) PW_HSM_EVENT_ADV(name_, _PW_HSM_VISITOR(sm_), ##__VA_ARGS__)

/**
* @brief Advanced version of @ref PW_HSM_EVENT where the visitor class name
*        is explicitly provided
*/	
#define PW_HSM_EVENT_ADV(name_, visitor_, ...)\
	class visitor_;\
	class name_ : public ::pw::hsm::EventBase<name_, visitor_> {\
	public:\
		PW_MAP(_PW_HSM_EVENT,##__VA_ARGS__)\
	}

/**
* @brief Define a visitor class named @ref name_
* @param name_ Name of the visitor class
* @param ... List of event class names that can be visited
*/
#define PW_HSM_VISITOR_ADV(name_, ...)\
	_PW_HSM_VISITOR_IMPL(name_, ##__VA_ARGS__)

/**
* @brief Declare traits (e.g., visitor) for a state machine
*/	
#define PW_HSM_TRAITS(name_, root_, ...)\
	class _PW_HSM_VISITOR(name_);\
	using _PW_HSM_ROOT(name_) = root_;\
	PW_HSM_VISITOR_ADV(_PW_HSM_VISITOR(name_), ##__VA_ARGS__)

/**
* @brief Declare a state machine class
*
* @param name_ The name of the state machine
*/	
#define PW_HSM(name_) PW_HSM_ADV(name_, _PW_HSM_VISITOR(name_), _PW_HSM_ROOT(name_))

/**
* @brief Advanced version of @ref PW_HSM where the visitor class name and root
*        state name are explicitly provided
*/	
#define PW_HSM_ADV(name_, visitor_, root_)\
	class name_ : public ::pw::hsm::StateMachine<name_, visitor_, root_>

/**
* @param sm_ The name of the state machine
* @param name_ The name of the state (class)
* @param parent_ The name of this state's parent state (class)
* @param ... List of child states
*/
#define PW_HSM_STATE(sm_, name_, parent_, ...) PW_HSM_STATE_ADV(name_, _PW_HSM_VISITOR(sm_), parent_, ##__VA_ARGS__)

/**
* @brief Advanced version of @ref PW_HSM_STATE where the visitor class name is
*        explicitly provided
*/			
#define PW_HSM_STATE_ADV(name_, visitor_, parent_, ...)\
	class name_:\
		public ::pw::hsm::State<name_, visitor_, parent_, ##__VA_ARGS__>
			
//------------------------------------------------------------------------------

#define _PW_HSM_VISITOR(name_) _##name_##_VISITOR
#define _PW_HSM_ROOT(name_) _##name_##_ROOT

//------------------------------------------------------------------------------

#define _PW_HSM_EVENT(x_) _PW_HSM_EVENTX x_
#define _PW_HSM_EVENTX(...) _PW_HSM_EVENTN(_0, ##__VA_ARGS__, _PW_HSM_EVENTN2, _PW_HSM_EVENTN1, _PW_HSM_EVENTN0)(__VA_ARGS__)
#define _PW_HSM_EVENTN(_0, _1, _2, FN_, ...) FN_
#define _PW_HSM_EVENTN0()
#define _PW_HSM_EVENTN1(type_) static_assert(false, "PW_HSM_EVENT: Invalid argument");
#define _PW_HSM_EVENTN2(type_, name_) type_ name_;

//------------------------------------------------------------------------------

#define _PW_HSM_VISITOR_IMPL(name_, ...)\
	class name_ {\
	public:\
		PW_MAP(_PW_HSM_VISITOR_IMPL_VISIT, ##__VA_ARGS__)\
	}
#define _PW_HSM_VISITOR_IMPL_VISIT(name_)\
	virtual ::pw::hsm::return_type visit(const name_& e) { return ::pw::hsm::PASS; }

#endif //PW_HSM_MACROS_HPP_