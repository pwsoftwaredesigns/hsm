#ifndef ABSTRACT_EVENT_HPP_
#define ABSTRACT_EVENT_HPP_

#include "_common.hpp"

//-----[ TEMPLATE CLASS: AbstractEvent ]----------------------------------------
template <typename VISITOR>
class AbstractEvent {
public:
	using visitor_type = VISITOR;
	
public:
	virtual state_return_type accept(visitor_type& visitor) const = 0;
	virtual const char* name() const = 0;
};

#endif //ABSTRACT_EVENT_HPP_