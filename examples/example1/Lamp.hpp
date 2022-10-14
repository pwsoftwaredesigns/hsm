#ifndef EXAMPLES_EXAMPLE3_LAMP_HPP_
#define EXAMPLES_EXAMPLE3_LAMP_HPP_

#include "common.hpp"

//You MUST include definitions of ALL CHILDREN for this to compile
#include "LampOn.hpp"
#include "LampOff.hpp"
#include "LampDead.hpp"

namespace lamp {

PW_HSM_STATE(
	StateMachine, //State Machine
	Lamp,         //Name of state
	StateMachine, //Parent
	
	LampOff,      //Child 0  (root)
	LampOn  ,     //Child 1
	LampDead      //Child 2
)
{
public:
	Lamp(parent_type& parent);
	~Lamp();
	
public:
	unsigned int toggleCount;
};

} //namespace lamp

#endif //EXAMPLES_EXAMPLE3_LAMP_HPP_