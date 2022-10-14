#ifndef EXAMPLES_EXAMPLE3_EVENTS_HPP_
#define EXAMPLES_EXAMPLE3_EVENTS_HPP_

#include <pw/hsm/includes.hpp>

namespace lamp {

PW_HSM_EVENT(
	StateMachine,
	EPowerButtonPressed,
	()
);

} //namespace lamp

#endif //EXAMPLES_EXAMPLE3_EVENTS_HPP_