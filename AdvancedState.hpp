#ifndef ADVANCEDSTATE_HPP_
#define ADVANCEDSTATE_HPP_

#include "State.hpp"

//-----[ TEMPLATE CLASS: State ]------------------------------------------------
template <typename CTX, typename T, typename PARENT, typename ... CHILDREN>
class State : 
	public State<CTX, T, PARENT, CHILDREN...>
{
public:
	void defer(const abstract_event_type& e) {
		_deferQ.push(e.clone());
	}
	
private:
	//Defer queue
	std::queue<std::unique_ptr<abstract_event_type>> _deferQ;
	
	//History
};

#endif //ADVANCEDSTATE_HPP_