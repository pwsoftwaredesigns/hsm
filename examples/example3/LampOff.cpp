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

::pw::hsm::state_return_type LampOff::visit(const EPowerButtonPressed& e)  {
	std::cout << "Turning lamp on" << std::endl;
	return transition<LampOn>();
}

} //namespace lamp