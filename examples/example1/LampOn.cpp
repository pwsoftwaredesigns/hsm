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

::pw::hsm::return_type LampOn::visit(const EPowerButtonPressed& e) {
	std::cout << "Turning lamp off" << std::endl;
	++parent().toggleCount;
	return transition<LampOff>();
}

} //namespace lamp