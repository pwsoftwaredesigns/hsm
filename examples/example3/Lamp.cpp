#include "includes.hpp"

namespace lamp {

Lamp::Lamp(parent_type& parent) :
	State(parent)
{
	PRINT_TRACE();
}

Lamp::~Lamp() {
	PRINT_TRACE();
}

} //namespace lamp