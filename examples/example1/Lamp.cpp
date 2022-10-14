#include "includes.hpp"

namespace lamp {

Lamp::Lamp(parent_type& parent) :
	State(parent),
	
	toggleCount(0)
{
	PRINT_TRACE();
}

Lamp::~Lamp() {
	PRINT_TRACE();
}

} //namespace lamp