#ifndef EXAMPLES_EXAMPLE3_LAMP_HPP_
#define EXAMPLES_EXAMPLE3_LAMP_HPP_

#include "common.hpp"
#include "LampOn.hpp"
#include "LampOff.hpp"

namespace lamp {

PW_HSM_STATE(StateMachine, Lamp, StateMachine, LampOff, LampOn)
{
public:
	Lamp(parent_type& parent);
	~Lamp();
};

} //namespace lamp

#endif //EXAMPLES_EXAMPLE3_LAMP_HPP_