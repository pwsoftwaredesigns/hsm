#ifndef EVENT_HPP_
#define EVENT_HPP_

#include "_common.hpp"
#include "AbstractEvent.hpp"

//-----[ TEMPLATE CLASS: Event ]------------------------------------------------
template <typename NAME, typename VISITOR, typename ... ARGS> 
class Event : public AbstractEvent<VISITOR>
{
public:
	using visitor_type = VISITOR;
	
public:
	Event(ARGS&& ... args):
		_args(std::forward<ARGS>(args)...)
	{
		
	}
	
public:
	state_return_type accept(visitor_type& visitor) const override {
		return visitor.visit(*this);
	}
	
	template <unsigned int N = 0>
	auto arg() const { return std::get<N>(_args); }
		
	const char* name() const override { return NAME::value(); }
	
private:
	std::tuple<ARGS...> _args;
};

#endif //EVENT_HPP_