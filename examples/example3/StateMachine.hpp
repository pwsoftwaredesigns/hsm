#ifndef EXAMPLES_EXAMPLE3_STATEMACHINE_HPP_
#define EXAMPLES_EXAMPLE3_STATEMACHINE_HPP_

#include "common.hpp"
#include "Lamp.hpp"

namespace lamp {

PW_HSM_STATE_MACHINE(StateMachine) 
{
public:
	StateMachine();
	~StateMachine();
};

} //namespace lamp

#endif //EXAMPLES_EXAMPLE3_STATEMACHINE_HPP_