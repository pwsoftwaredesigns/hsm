#include "includes.hpp"

namespace lamp {

LampDead::LampDead(parent_type& parent) :
	State(parent)
{
	PRINT_TRACE();
}

LampDead::~LampDead() {
	PRINT_TRACE();
}

::pw::hsm::return_type LampDead::visit(const EPowerButtonPressed& e)  {
	std::cout << "You can't turn a dead lamp on :(" << std::endl;
		
	return pw::hsm::PASS;
}

} //namespace lamp