/**
* @brief Common header included by all HEADER (*.hpp) files in the state
*        machine
*/

#ifndef EXAMPLES_EXAMPLE3_COMMON_HPP_
#define EXAMPLES_EXAMPLE3_COMMON_HPP_

#include "../common.hpp"
#include <pw/hsm/includes.hpp>

namespace lamp {

//Forward-declaration of all states
class StateMachine;
	class Lamp;
		class LampOff;
		class LampOn;

//Declaration of the state machine traits and events
PW_HSM_STATE_MACHINE_TRAITS(
	StateMachine, 
	Lamp,
	(EPowerButtonPressed)
);

} //namespace lamp

#endif //EXAMPLES_EXAMPLE3_COMMON_HPP_