#ifndef EXAMPLES_EXAMPLE3_COMMON_HPP_
#define EXAMPLES_EXAMPLE3_COMMON_HPP_

#include "../common.hpp"
#include <pw/hsm/includes.hpp>

namespace lamp {

class StateMachine;
	class Lamp;
		class LampOff;
		class LampOn;

PW_HSM_STATE_MACHINE_TRAITS(
	StateMachine, 
	Lamp,
	(EPowerButtonPressed)
);

} //namespace lamp

#endif //EXAMPLES_EXAMPLE3_COMMON_HPP_