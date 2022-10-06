#ifndef PW_HSM_ABSTRACT_EVENT_HPP_
#define PW_HSM_ABSTRACT_EVENT_HPP_

#include "_common.hpp"

namespace pw::hsm {

//-----[ TEMPLATE CLASS: AbstractEvent ]----------------------------------------
template <typename VISITOR>
class AbstractEvent {
public:
	using visitor_type = VISITOR;
	
public:
	virtual state_return_type accept(visitor_type& visitor) const = 0;
	virtual const char* name() const = 0;
};

} //namespace pw::hsm

#endif //PW_HSM_ABSTRACT_EVENT_HPP_