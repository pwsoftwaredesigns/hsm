#ifndef EXAMPLES_EXAMPLE3_LAMPOFF_HPP_
#define EXAMPLES_EXAMPLE3_LAMPOFF_HPP_

#include "common.hpp"

namespace lamp {

PW_HSM_STATE(StateMachine, LampOff, Lamp)
{
public:
	LampOff(parent_type& parent);
	~LampOff();
	::pw::hsm::return_type visit(const EPowerButtonPressed& e) override;
};

} //namespace lamp

#endif //EXAMPLES_EXAMPLE3_LAMPOFF_HPP_