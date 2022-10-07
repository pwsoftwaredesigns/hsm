#include "includes.hpp"

namespace lamp {

LampOn::LampOn(parent_type& parent) :
	State(parent)
{
	PRINT_TRACE();
}

LampOn::~LampOn() {
	PRINT_TRACE();
}

::pw::hsm::state_return_type LampOn::visit(const EPowerButtonPressed& e) {
	std::cout << "Turning lamp off" << std::endl;
	return transition<LampOff>();
}

} //namespace lamp