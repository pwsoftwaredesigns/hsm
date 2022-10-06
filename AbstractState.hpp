#ifndef ABSTRACTSTATE_HPP_
#define ABSTRACTSTATE_HPP_

#include "_common.hpp"

//-----[ TEMPLATE CLASS: AbstractState ]----------------------------------------
template <typename VISITOR>
class AbstractState :
	public VISITOR
{
	template <typename T_, typename PARENT_, typename ... CHILDREN_>
	friend
	class State;
	
	template <typename CTX_, typename ROOT_>
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
	
	virtual ctti::detail::cstring name() const = 0;
	virtual ctti::detail::cstring childName() const = 0;
			
private:
	virtual void _init() {}
	virtual void _deinit() {}
};

#endif //ABSTRACTSTATE_HPP_