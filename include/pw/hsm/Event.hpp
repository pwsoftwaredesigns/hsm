#ifndef PW_HSM_EVENT_HPP_
#define PW_HSM_EVENT_HPP_

#include "_common.hpp"
#include "AbstractEvent.hpp"
#include <tuple>

namespace pw::hsm {
	
//-----[ TEMPLATE CLASS: EventBase ]--------------------------------------------
template <typename T, typename VISITOR>
class EventBase : public AbstractEvent<VISITOR>
{
public:
	using visitor_type = VISITOR;
	
public:
	return_type accept(visitor_type& visitor) const override {
		return visitor.visit(static_cast<const T&>(*this));
	}
	
	name_string_type name() const override { return ctti::nameof<T>(); }
};

//-----[ TEMPLATE CLASS: Event ]------------------------------------------------
template <typename NAME, typename VISITOR, typename ... ARGS> 
class Event : public EventBase<Event<NAME, VISITOR, ARGS...>, VISITOR>
{
public:
	using visitor_type = VISITOR;
	
public:
	template <typename ... ARGS_>
	Event(ARGS_&& ... args):
		_args(std::forward<ARGS_>(args)...)
	{
		
	}
	
public:
	return_type accept(visitor_type& visitor) const override {
		return visitor.visit(*this);
	}
	
	template <unsigned int N = 0>
	auto arg() const { return std::get<N>(_args); }
		
	name_string_type name() const final { return NAME::value(); }
	
private:
	std::tuple<ARGS...> _args;
};

} //namespace pw::hsm

#endif //PW_HSM_EVENT_HPP_