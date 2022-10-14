/**
* @brief Common header included by all HEADER (*.hpp) files in the state
*        machine
*/

#ifndef EXAMPLES_EXAMPLE3_COMMON_HPP_
#define EXAMPLES_EXAMPLE3_COMMON_HPP_

#include "../common.hpp"
#include <pw/hsm/includes.hpp>
#include "events.hpp"

namespace lamp {
	
constexpr unsigned int MAX_TOGGLES = 4;

//Forward-declaration of all states
class StateMachine;
	class Lamp;
		class LampDead;
		class LampOff;
		class LampOn;

PW_HSM_TRAITS(
	StateMachine,
	Lamp,
	
	EPowerButtonPressed
);

} //namespace lamp

#endif //EXAMPLES_EXAMPLE3_COMMON_HPP_