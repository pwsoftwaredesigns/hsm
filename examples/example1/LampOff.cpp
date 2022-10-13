#include "includes.hpp"

namespace lamp {

LampOff::LampOff(parent_type& parent) :
	State(parent)
{
	PRINT_TRACE();
}

LampOff::~LampOff() {
	PRINT_TRACE();
}

::pw::hsm::return_type LampOff::visit(const EPowerButtonPressed& e)  {
	if (++parent().toggleCount < lamp::MAX_TOGGLES) {
		std::cout << "Turning lamp on" << std::endl;
		return transition<LampOn>();
	} else {
		//The lamp burns out
		std::cout << "The lamp has burned up" << std::endl;
		return transition<LampDead>();
	}
}

} //namespace lamp