#ifndef ABSTRACTSTATE_HPP_
#define ABSTRACTSTATE_HPP_

#include "_common.hpp"

//-----[ TEMPLATE CLASS: AbstractState ]----------------------------------------
template <typename CTX>
class AbstractState :
	public state_machine_traits<CTX>::visitor_type
{
	template <typename CTX_, typename T_, typename PARENT_, typename ... CHILDREN_>
	friend
	class State;
	
	template <typename CTX_, typename ROOT_>
	friend
	class StateMachine;
	
	using visitor_type = typename state_machine_traits<CTX>::visitor_type;
	
public:
	AbstractState() = default;
	virtual ~AbstractState() = default;
	
public:
	virtual state_return_type dispatch(const AbstractEvent<visitor_type>& e) {
		return e.accept(*this);
	}
	
	virtual ctti::detail::cstring name() const = 0;
	virtual ctti::detail::cstring childName() const = 0;
			
private:
	virtual void _init() {}
	virtual void _deinit() {}
};

#endif //ABSTRACTSTATE_HPP_