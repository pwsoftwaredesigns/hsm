#ifndef PW_HSM_ABSTRACTSTATE_HPP_
#define PW_HSM_ABSTRACTSTATE_HPP_

#include "_common.hpp"
#include "AbstractEvent.hpp"
#include <ctti/detail/cstring.hpp>

namespace pw::hsm {

//-----[ TEMPLATE CLASS: AbstractState ]----------------------------------------
template <typename VISITOR>
class AbstractState :
	public VISITOR
{
	template <typename T_, typename VISITOR_, typename PARENT_, typename ... CHILDREN_>
	friend
	class State;
	
	template <typename CTX_, typename VISITOR_, typename ROOT_>
	friend
	class StateMachine;
	
public:
	AbstractState() = default;
	virtual ~AbstractState() = default;
	
	AbstractState(const AbstractState&) = delete;
	AbstractState& operator=(const AbstractState&) = delete;
	
public:
	virtual state_return_type dispatch(const AbstractEvent<VISITOR>& e) {
		return e.accept(*this);
	}
	
	virtual name_string_type name() const = 0;
	virtual name_string_type childName() const = 0;
			
private:
	virtual void _init() {}
	virtual void _deinit() {}
};

} //namespace pw::hsm

#endif //PW_HSM_ABSTRACTSTATE_HPP_